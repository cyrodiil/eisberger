<?php

/**
 * Implements hook_panels_layouts().
 */
function eisberger_eisberger_fourcol_3_9_panels_layouts() {
  $items['eisberger_fourcol_3_9'] = array(
    'title' => t('Four Column 3-9 stacked'),
    'category' => t('eisberger'),
    'icon' => 'eisberger_fourcol_3_9.png',
    'theme' => 'eisberger_fourcol_3_9',
    'admin css' => '../eisberger_panels_admin_12.css',
    'regions' => array(
      'top' => t('Top'),
      'topleft' => t('Top Left'),
      'topright' => t('Top Right'),
      'smallleft' => t('Small Left'),
      'bigright' => t('Big Right'),      
      'middleleft' => t('Middle Left'),
      'middleleftcenter' => t('Middle Left Center'),
      'middlerightcenter' => t('Middle Right Center'),
      'middleright' => t('Middle Right'),
      'bigleft' => t('Big Left'),
      'smallright' => t('Small Right'),
      'bottomleft' => t('Bottom Left'),
      'bottomright' => t('Bottom Right'),
      'bottommiddleleft' => t('Bottom Middle Left'),
      'bottommiddleleftcenter' => t('Bottom Middle Left Centetr'),
      'bottommiddlerightcenter' => t('Bottom Middle Right Center'),
      'bottommiddleright' => t('Bottom Middle Right'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
