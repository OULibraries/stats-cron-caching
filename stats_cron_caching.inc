<?php


/**
 * Implements hook_cron().
 */
function stats_cron_caching_cron() {

//  $urls = 'http://newstats.dd:8083/servicecontacts,newstats.dd:8083';

  // we get the urls that the user entered and call the curl function
  $urls = variable_get('cron_caching_urls');
  call_curl_urls($urls);
}

/**
 * @param $urls
 * Loop through the urls entered and curl each one
 * We don't care about the data because all we want to do is load the page
 */
function call_curl_urls($urls) {
  $arrayedUrls = explode(',', $urls);

  foreach ($arrayedUrls as $tempUrl) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $tempUrl);
    curl_exec($ch);
  }
}

/**
 * Below this line is simply setting up the configuration options and setting
 * up the permissions for the configuration options
 */

/**
 * Implements hook_menu().
 */
function stats_cron_caching_menu() {
  /* proxy settings */
  $items['admin/config/system/stats_cron_caching']
    = array(
    'title' => 'Stats Cron URL Caching',
    'description' => 'Give URLs for the cron to cache',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('stats_cron_caching_settings'),
    'access arguments' => array('administer stats_cron_caching settings'),
    'weight' => -10,
  );

  return $items;
}

function stats_cron_caching_permission() {
  $modperms = array(
    'administer stats_cron_caching settings' => array(
      'title' => t('Administer Cron caching settings'),
    ),
  );
  return $modperms;
}

function stats_cron_caching_settings() {

  $form = array();

  $form['cron_caching_urls'] = array(
    '#type' => 'textfield',
    '#title' => t('Cron Caching URLs'),
    '#default_value' => variable_get('cron_caching_urls', ""),
    '#description' => t("The URLs for the Cron to cache. Enter a comma separated
    list without spaces after the commas"),
    '#required' => FALSE,
  );

  return system_settings_form($form);

}