<?php

/**
 * Implements hook_panels_layouts().
 */
function eisberger_eisberger_threecol_4_8_panels_layouts() {
  $items['eisberger_threecol_4_8'] = array(
    'title' => t('Three Column 4-8 stacked'),
    'category' => t('eisberger'),
    'icon' => 'eisberger_threecol_4_8.png',
    'theme' => 'eisberger_threecol_4_8',
    'admin css' => '../eisberger_panels_admin_12.css',
    'regions' => array(
      'top' => t('Top'),
      'smallleft' => t('Small Left'),
      'bigright' => t('Big Right'),
      'topleft' => t('Top Left'),
      'topcenter' => t('Top Center'),
      'topright' => t('Top Right'),
      'bigleft' => t('Big Left'),
      'smallright' => t('Small Right'),
      'bottomleft' => t('Bottom Left'),
      'bottomcenter' => t('Bottom Center'),
      'bottomright' => t('Bottom Right'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
