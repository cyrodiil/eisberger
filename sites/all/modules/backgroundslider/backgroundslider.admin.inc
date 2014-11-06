<?php
/**
 * @file
 * Administration forms for background entities and module.
 */

/**
 * Form for adding / editing a background entity.
 */
function backgroundslider_form($form, &$form_state, $background = NULL) {

  if (!$background->is_new) {
    $image = file_load($background->fid);
    if ($image) {
      $form['image'] = array(
        '#type' => 'markup',
        '#markup' => theme_image(array('path' => $image->uri, 'height' => '100px')),
      );

      $form['old_fid'] = array(
        '#type' => 'value',
        '#value' => $background->fid,
      );
    }
  }

  $form['fid'] = array(
    '#title' => t('Background image'),
    '#type' => 'managed_file',
    '#description' => t('File name.'),
    '#required' => ($background->is_new) ? TRUE : FALSE,
    '#upload_location' => 'public://backgrounds/',
  );

  $form['status'] = array(
    '#title' => t('Enabled'),
    '#type' => 'checkbox',
    '#description' => t('If not set to enabled, background will not show up in the slider'),
    '#default_value' => isset($background->status) ? $background->status : 1,
  );

  $form['color'] = array(
    '#title' => t('Color'),
    '#type' => 'textfield',
    '#default_value' => isset($background->color) ? $background->color : '',
    '#description' => t('Color for selected elements.'),
    '#required' => TRUE,
    '#size' => '6',
    '#maxlength' => '6',
    '#field_prefix' => '#',
  );

  $form['elements'] = array(
    '#title' => t('Elements to apply color to'),
    '#type' => 'textarea',
    '#default_value' => isset($background->elements) ? $background->elements : '',
    '#description' => t('CSS selectors for all elements which should have the selected color. One element per line.'),
    '#required' => FALSE,
  );

  $form['visibility'] = array(
    '#title' => t('Show background on specific pages'),
    '#type' => 'radios',
    '#default_value' => isset($background->visibility) ? $background->visibility : 0,
    '#required' => TRUE,
    '#options' => array(
      0 => t('All pages except those listed'),
      1 => t('Only the listed pages '),
    ),
  );

  $form['pages'] = array(
    '#title' => t('Pages'),
    '#title_display' => 'invisible',
    '#type' => 'textarea',
    '#default_value' => isset($background->pages) ? $background->pages : '',
    '#required' => FALSE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($background->id) ? t('Update background') : t('Save background'),
    ),
  );

  return $form;
}

/**
 * Validation for background entity form.
 */
function backgroundslider_form_validate($form, &$form_state) {
  if (isset($form_state['values']['color']) && !ctype_xdigit($form_state['values']['color'])) {
    form_set_error('color', t('Color field must be a hexadecimal value.'));
  }
  elseif (strlen($form_state['values']['color']) != 6) {
    form_set_error('color', t('Color field must be exactly 6 characters long.'));
  }
}

/**
 * Submit handler for background entity form.
 */
function backgroundslider_form_submit($form, &$form_state) {

  $background = entity_ui_form_submit_build_entity($form, $form_state);

  if ($form_state['background']->is_new) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'backgroundslider');
    $query->count();
    $count = $query->execute();
    $background->weight = $count;
  }

  if ($form_state['background']->is_new || (!$form_state['background']->is_new && $form_state['values']['fid'] != 0)) {
    // Load uploaded file.
    $image = file_load($form_state['values']['fid']);
    // Mark file as permanent and save.
    $image->status = FILE_STATUS_PERMANENT;
    file_save($image);
    $background->filename = $image->filename;
    $add_usage = TRUE;
  }
  elseif (!$form_state['background']->is_new && $form_state['values']['fid'] == 0) {
    $background->fid = $form_state['values']['old_fid'];
    $add_usage = FALSE;
  }

  $background->save();

  if ($add_usage) {
    // Record that the module is using the file.
    file_usage_add($image, 'backgroundslider', 'backgroundslider', $background->bid);
  }

  drupal_set_message(t('@name background has been saved.', array('@name' => $background->filename)));
  cache_clear_all('backgroundslider', 'cache');
  $form_state['redirect'] = 'admin/appearance/background';
}

/**
 * Configuration form for backgroundslider.
 */
function backgroundslider_admin() {

  $form = array();

  $form['backgroundslider_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Delay'),
    '#description' => t('The time delay between two backgrounds in miliseconds.'),
    '#default_value' => variable_get('backgroundslider_delay', 5000),
    '#required' => TRUE,
    '#size' => 6,
  );

  $form['backgroundslider_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Transition duration'),
    '#description' => t('The duration of the background transition animation.'),
    '#default_value' => variable_get('backgroundslider_speed', 400),
    '#required' => TRUE,
    '#size' => 6,
  );

  $form['backgroundslider_effect'] = array(
    '#type' => 'select',
    '#title' => t('Transition effect'),
    '#description' => t('The duration of the background transition animation.'),
    '#default_value' => variable_get('backgroundslider_effect', 'fade'),
    '#options' => array(
      'none' => t('None'),
      'fade' => t('Fade'),
      'simpleSlide' => t('Simple Slider'),
      'superSlide' => t('Super Slider'),
    ),
  );

  $form['backgroundslider_sequence'] = array(
    '#type' => 'select',
    '#title' => t('Sequence mode'),
    '#description' => t('The sequence of the images.'),
    '#default_value' => variable_get('backgroundslider_sequence', 'normal'),
    '#options' => array(
      'normal' => t('Normal'),
      'back' => t('Back'),
      'random' => t('Random'),
    ),
  );

  $form['backgroundslider_direction'] = array(
    '#type' => 'select',
    '#title' => t('Slide direction'),
    '#description' => t('The direction of the slide animation.'),
    '#default_value' => variable_get('backgroundslider_direction', 'N'),
    '#options' => array(
      'N' => t('North'),
      'S' => t('South'),
      'W' => t('West'),
      'E' => t('East'),
      'NW' => t('North-West (only with Super Slider)'),
      'NE' => t('North-East (only with Super Slider)'),
      'SW' => t('South-West (only with Super Slider)'),
      'SE' => t('South-East (only with Super Slider)'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="backgroundslider_effect"]' => array(
          array('value' => 'simpleSlide'),
          array('value' => 'superSlide'),
        ),
      ),
    ),
  );

  $form['backgroundslider_random'] = array(
    '#type' => 'checkbox',
    '#title' => t('Start with random image'),
    '#description' => t('If checked, the slideshow will start with a random image, but continue with the normal sequence.'),
    '#default_value' => variable_get('backgroundslider_random', 0),
  );

  $form['backgroundslider_opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Element opacity'),
    '#description' => t('Opacity of the elements which receive the color defined in the backgrounds. From 0 to 1.'),
    '#default_value' => variable_get('backgroundslider_opacity', 1),
    '#required' => TRUE,
    '#size' => 3,
  );

  $form['backgroundslider_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Image width'),
    '#description' => t('Width of the images you have uploaded as backgrounds.'),
    '#default_value' => variable_get('backgroundslider_width', 1920),
    '#required' => TRUE,
    '#size' => 4,
  );

  $form['backgroundslider_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Image height'),
    '#description' => t('Height of the images you have uploaded as backgrounds.'),
    '#default_value' => variable_get('backgroundslider_height', 1080),
    '#required' => TRUE,
    '#size' => 4,
  );

  return system_settings_form($form);
}

/**
 * Validation callback for configuration form.
 */
function backgroundslider_admin_validate($form, &$form_state) {
  if (!ctype_digit($form_state['values']['backgroundslider_speed'])) {
    form_set_error('backgroundslider_delay', t('The delay has to be a number.'));
  }

  if (!ctype_digit($form_state['values']['backgroundslider_speed'])) {
    form_set_error('backgroundslider_speed', t('The duration has to be a number.'));
  }

  if (!is_numeric($form_state['values']['backgroundslider_opacity'])) {
    form_set_error('backgroundslider_opacity', t('The opacity has to be a numeric value.'));
  }

  if (floatval($form_state['values']['backgroundslider_opacity']) < 0 || floatval($form_state['values']['backgroundslider_opacity']) > 1) {
    form_set_error('backgroundslider_opacity', t('The opacity has to be a value between 0 and 1.'));
  }

  if (!ctype_digit($form_state['values']['backgroundslider_width'])) {
    form_set_error('backgroundslider_width', t('The image width has to be a number.'));
  }

  if (!ctype_digit($form_state['values']['backgroundslider_height'])) {
    form_set_error('backgroundslider_height', t('The image height has to be a number.'));
  }
}
