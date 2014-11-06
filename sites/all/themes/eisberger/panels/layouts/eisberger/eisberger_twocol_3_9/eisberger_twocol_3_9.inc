<?php

/**
 * Implements hook_panels_layouts().
 */
function eisberger_eisberger_twocol_3_9_panels_layouts() {
  $items['eisberger_twocol_3_9'] = array(
    'title' => t('Two Column 3-9 stacked'),
    'category' => t('eisberger'),
    'icon' => 'eisberger_twocol_3_9.png',
    'theme' => 'eisberger_twocol_3_9',
    'admin css' => '../eisberger_panels_admin_12.css',
    'regions' => array(
      'top' => t('Top'),
      'left' => t('Left'),
      'right' => t('Right'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}
