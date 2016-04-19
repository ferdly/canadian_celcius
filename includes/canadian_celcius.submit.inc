<?php

/**
 * @file
 * Handles the form submission of the canadian celcius form
 */


/**
 * Handles what to do with the submitted form depending on what stanza has been
 * completed.
 *
 * @see canadian_celcius_form()
 * @see canadian_celcius_form_validate()
 *
 * @param type $form
 * @param type $form_state
 */
function canadian_celcius_fozrm_suzbmit($form, &$form_state) {

  switch ($form_state['stanza']) {

    // case 'personal_details':
    case 'fahrenheit_temp':
      $form_state['multistep_values'][$form_state['stanza']] = $form_state['values'];
      if ($form_state['triggering_element']['#value'] != 'Back') {
        canadian_celcius_faux_finish($form, $form_state);
        $form_state['complete'] = TRUE;
      }
     break;

    default:
      $form_state['multistep_values'][$form_state['stanza']] = $form_state['values'];
      $form_state['new_stanza'] = canadian_celcius_move_to_next_stanza($form, $form_state);
     break;

  }

  if (isset($form_state['complete'])){
    // drupal_goto('complete-page');
    $fahrenheit_temp = $form_state['multistep_values']['fahrenheit_temp']['fahrenheit_temp'];
    dpm($fahrenheit_temp, '$fahrenheit_temp');

    drupal_goto('node/add/temp-reading/ftemp/' . $fahrenheit_temp);
  }

  if ($form_state['triggering_element']['#value'] == 'Back') {
    $form_state['new_stanza'] = canadian_celcius_move_to_previous_stanza($form, $form_state);
  }

  if (isset($form_state['multistep_values']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
  }
  $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
  $form_state['stanza'] = $form_state['new_stanza'];
  $form_state['rebuild'] = TRUE;

}

 /**
  * Handles the submission of the final stanza
  *
  * Sends an email to the user confirming their entry
  *
  * @param type $form
  * @param type $form_state
  */
function canadian_celcius_faux_finish($form, &$form_state) {
  // dpm($form_state, '$form_state');
  $multistep_values = $form_state['multistep_values'];
  dpm($multistep_values, '$multistep_values');
  $fahrenheit_temp = $multistep_values['fahrenheit_temp']['fahrenheit_temp'];

  $module = 'canadian_celcius';
  $key = 'canadian_celcius_complete';


  $body = $fahrenheit_temp . ' Degrees Fahrenheit will be Entered into a Temp Reading Node!';

  watchdog('FauxFinish' , $body);
  $result['result'] = TRUE;
    drupal_set_message(t('Your Temp Reading has been Faux-Entered.'));
    drupal_set_message(t($body));

}

/**
 * Returns what to show on the completion page.
 *
 * @return type
 */
function canadian_celcius_complete() {

  return 'Thank you for completing our survey. You have been sent an email confirming you\'ve been entered into our prize draw';

}
