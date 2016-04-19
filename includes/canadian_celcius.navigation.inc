<?php

/**
 * @file
 * Handles the navigation of the canadian celcius form
 * All hooks are in the .module file.
 */


/**
 * Given the current stanza the user is on, calculate what the next step would be
 *
 * @param type $form_state
 * @return string
 */
function canadian_celcius_move_to_next_stanza($form, &$form_state) {

  switch ($form_state['stanza']) {
    case 'celcius_temp':
      return 'fahrenheit_temp';
     break;

    case 'fahrenheit_temp':
      return 'personal_details';
     break;
  }

}


/**
 * Given the current stanza the user is on, calculate what the previous step
 * would be
 *
 * @param type $form_state
 * @return string
 */

function canadian_celcius_move_to_previous_stanza($form, &$form_state) {

  switch ($form_state['stanza']) {
    case 'rate_the_service':
      return 'rate_the_room';
     break;

    case 'personal_details':
      return 'rate_the_service';
     break;
  }

}