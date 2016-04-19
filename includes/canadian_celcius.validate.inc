<?php

/**
 * @file
 * Handles the form validation of the canadian celcius form
 * All hooks are in the .module file.
 */


/**
 * Master validation function for the canadian celcius form - uses per-stanza
 * validation and calls functions for each one.
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function canadian_celcius_form_validate($form, &$form_state) {

  if ($form_state['triggering_element']['#value'] == 'Back') {
    return;
  }

  switch ($form_state['stanza']) {

    case 'rate_the_room':
      return canadian_celcius_rate_the_room_vazlidate($form, $form_state);
     break;

    case 'rate_the_service':
      return canadian_celcius_rate_the_service_vazlidate($form, $form_state);
     break;

    case 'personal_details':
      return canadian_celcius_personal_details_vazlidate($form, $form_state);
     break;

  }
}


/**
 * Validation for the rate_the_room step
 *
 * @param type $form
 * @param type $form_state
 */
function canadian_celcius_rate_the_room_vazlidate($form, &$form_state) {
  if (!$form_state['values']['room_rating']) {
    form_set_error('room_rating', 'You must rate our room before continuing');
  }
}


/**
 * Validation for the rate_the_service step
 *
 * @param type $form
 * @param type $form_state
 */
function canadian_celcius_rate_the_service_vazlidate($form, &$form_state) {
  if (!$form_state['values']['service_rating']) {
    form_set_error('service_rating', 'You must rate our service before continuing');
  }
}


/**
 * Validation for the personal_details step
 *
 * @param type $form
 * @param type $form_state
 */
function canadian_celcius_personal_details_vazlidate($form, &$form_state) {
  if (!$form_state['values']['name']) {
    form_set_error('name', 'You must enter a name before continuing');
  }

  if (!valid_email_address($form_state['values']['email'])) {
    form_set_error('email', 'You must enter a valid email address');
  }
}