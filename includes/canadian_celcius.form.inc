<?php

/**
 * @file
 * Handles the form elements of the canadian celcius form
 * All hooks are in the .module file.
 */

/**
 * Master form which calls an individual form for each step.
 *
 * @see canadian_celcius_form_validate().
 * @see canadian_celcius_form_submit().
 *
 * @param type $form
 * @param string $form_state
 * @return type
 */
function canadian_celcius_fozrm($form, &$form_state) {

  if (!isset($form_state['stanza'])){
    $form_state['stanza'] = 'celcius_temp';
  }

  $form = array();

  $form['#submit'][] = 'canadian_celcius_fozrm_suzbmit';
  switch ($form_state['stanza']) {

    case 'celcius_temp':
      return canadian_celcius_gather_celcius($form, $form_state);
     break;

    case 'fahrenheit_temp':
      return canadian_celcius_gather_fahrenheit_temp($form, $form_state);
     break;

    case 'personal_details':
      return canadian_celcius_personal_details_form($form, $form_state);
     break;

    default:
      return canadian_celcius_gather_celcius($form, $form_state);
     break;
  }
  return $form;
}


/**
 * Form for the celcius_temp step.
 *
 * @see canadian_celcius_form().
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function canadian_celcius_gather_celcius($form, &$form_state) {

  $values = isset($form_state['multistep_values']['celcius_temp']) ? $form_state['multistep_values']['celcius_temp'] : array();

  $form['celcius_temp'] = array(
    '#type' => 'textfield',
    '#size' => '4',
    '#title' => 'Enter the Temperature in Degrees Celcius',
    '#default_value' => isset($values['celcius_temp']) ? $values['celcius_temp'] : '15',
    '#suffix' => '&deg; C',
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next')
  );

return $form;
}


/**
 * Form for the fahrenheit_temp step.
 *
 * @see canadian_celcius_form().
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function canadian_celcius_gather_fahrenheit_temp($form, &$form_state) {

  $values = isset($form_state['multistep_values']['fahrenheit_temp']) ? $form_state['multistep_values']['fahrenheit_temp'] : array();
  $celcius_temp = isset($form_state['multistep_values']['celcius_temp']['celcius_temp']) ? $form_state['multistep_values']['celcius_temp']['celcius_temp'] + 0 : FALSE;
  $fahrenheit_temp = canadian_celcius_converter($celcius_temp);
  $title = "You entered {$celcius_temp} &deg; C which is {$fahrenheit_temp} &deg; F";
  $title = $celcius_temp === FALSE ? 'Enter the Temperature in Degrees Fahrenheit' : $title;
  $form['fahrenheit_temp'] = array(
    '#type' => 'textfield',
    '#size' => '4',
    '#title' => $title,
    '#default_value' => $fahrenheit_temp,
    '#suffix' => '&deg; F',
  );

  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Back')
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next')
  );

  return $form;
}


/**
 * Form for the personal_details step.
 *
 * @see canadian_celcius_form().
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function canadian_celcius_personal_details_form($form, &$form_state) {

  $values = isset($form_state['multistep_values']['personal_details']) ? $form_state['multistep_values']['personal_details'] : array();

  $form['personal_details']['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Name',
    '#default_value' => isset($values['name']) ? $values['name'] : NULL,
  );

  $form['personal_details']['email'] = array(
    '#type' => 'textfield',
    '#title' => 'Email',
    '#default_value' => isset($values['email']) ? $values['email'] : NULL,
  );

  $form['back'] = array(
    '#type' => 'submit',
    '#value' => t('Back')
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );

  return $form;
}

function canadian_celcius_converter($celcius_temp) {
  if ($celcius_temp === FALSE) {
    return '';
  }
  $fahrenheit_temp = $celcius_temp + 0;
  $fahrenheit_temp = $fahrenheit_temp * 9;
  $fahrenheit_temp = $fahrenheit_temp / 5;
  $fahrenheit_temp += 32;
  $fahrenheit_temp = round($fahrenheit_temp, 2);
  return $fahrenheit_temp;

}
