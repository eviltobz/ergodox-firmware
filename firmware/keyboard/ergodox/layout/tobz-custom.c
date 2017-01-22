/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * A Colemak and Qwerty layout with Mac and Windows optimisations
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 *
 * History:
 * - Originally submitted by Jason Trill [jjt] (https://github.com/jjt) (who
 *   declined to be added to the copyright above).
 * - Various changes have been made since (see git history)
 */


#include "./common/definitions.h"

#include "./common/keys.c.h"

// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

#include "./common/exec_key.c.h"


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

// TODO 
//
// have leds do normal keyboard flavour lights when in the admin layer, but layer lights when elsewhere
// any other statusy things that i can think of to have led indicator states???
// .....
// in admin mode, have the button with the led do the function.

void kb__led__logical_on(char led) {
    switch(led) {
        case 'N':                 break;  // numlock
        case 'C': kb__led__on(3); break;  // capslock
        case 'S':                 break;  // scroll lock
        case 'O':                 break;  // compose
        case 'K':                 break;  // kana
    };
}

void kb__led__logical_off(char led) {
    switch(led) {
        case 'N':                  break;  // numlock
        case 'C': kb__led__off(3); break;  // capslock
        case 'S':                  break;  // scroll lock
        case 'O':                  break;  // compose
        case 'K':                  break;  // kana
    };
}

void update_layout_leds(void) {
  ;
}

void pop_all(void) {
  kb__led__off(1);
  kb__led__off(2);
  //kb__led__off(3);
  layer_stack__pop_id(1);
  layer_stack__pop_id(2);
}
void keys__press__push_windows(void) {
  pop_all();
  //kb__led__off(1);
  layer_stack__push(0, 1, 1); 
  _flags.tick_keypresses = false;
  kb__led__on(1);
}
void keys__release__push_windows(void) {
  ;
}
void keys__press__push_qwerty(void) {
  pop_all();
  //kb__led__off(1);
  layer_stack__push(0, 2, 2); 
  _flags.tick_keypresses = false;
  kb__led__on(2);
}
void keys__release__push_qwerty(void) {
  ;
}
#define keys__press__popAll pop_all
#define keys__release__popAll pop_all

// Meaningful function names
#define LBase popAll
#define LTwin push_windows
#define LTqwe push_qwerty
#define LHnum lpupo3l3
#define LHdev lpupo4l4
#define LHadm lpupo5l5

/*
void kbfun_mediakey_press_release(void) {
  uint8_t keycode = kb_layout_get(LAYER, ROW, COL);
  _kbfun_mediakey_press_release(IS_PRESSED, keycode);
}

void _kbfun_mediakey_press_release(bool press, uint8_t keycode) {
  uint16_t mediakey_code = _media_code_lookup_table[keycode];
  if (press) {
    consumer_key = mediakey_code;
  } else {
    // Only one key can be pressed at a time so only clear the keypress for
    //  active key (most recently pressed)
    if (mediakey_code == consumer_key) {
      consumer_key = 0;
    }
  }
}
*/


// ----------------------------------------------------------------------------
// keys
// ----------------------------------------------------------------------------


KEYS__LAYER__NUM_PU_PO(10, 4);
KEYS__LAYER__NUM_PUSH(10, 4);
KEYS__LAYER__NUM_POP(10);


// ----------------------------------------------------------------------------
// layout
// ----------------------------------------------------------------------------

#include "./common/matrix.h"



static _layout_t _layout = {

// ............................................................................

// layer 0 -- Mac Layer
    MATRIX_LAYER(
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
   equal,        1,        2,        3,        4,        5,    home,
     tab,        q,        w,        f,        p,        g,     end,
     esc,        a,        r,        s,        t,        d,
nonUSBkslash,    z,        x,        c,        v,        b,    ctrlL,
   grave,      nop,      nop,    brktL,    brktR,
                                                                 del,     altL,
                                                       nop,      nop,     guiL,
                                                     LHnum,       bs,  shL2kcap,
// right hand ..... ......... ......... ......... ......... ......... .........
             pageU,        6,        7,        8,        9,        0,     dash,
             pageD,        j,        l,        u,        y,  semicol,  nonUSPound,
                           h,        n,        e,        i,        o,    quote,
             ctrlR,        k,        m,    comma,   period,   arrowU,    slash,
                                 brktL,    brktR,   arrowL,   arrowD,   arrowR,
    altR,    enter,
    guiR,      nop,      nop,
 shR2kcap,    space,    LHdev  ),

// layer 1 -- Windows layer
  MATRIX_LAYER(
	// unused
	K, nop,	
	// left hand
	transp,	transp,	transp,	transp,	transp,	transp,	transp,	
	transp,	transp,	transp,	transp,	transp,	transp,	transp,	
	transp,	transp,	transp,	transp,	transp,	transp,	
	transp,	transp,	transp,	transp,	transp,	transp,	guiL/**/,	
	transp,	transp,	transp,	transp,	transp,	
	        transp,	transp,	
	transp,	transp,	ctrlL/**/,	
	transp,	transp,	transp,	
	// right hand
	transp,	transp,	transp,	transp,	transp,	transp,	transp,	
	transp,	transp,	transp,	transp,	transp,	transp,	transp,	
	        transp,	transp,	transp,	transp,	transp,	transp,	
guiR/**/,	transp,	transp,	transp,	transp,	transp,	transp,	
	                transp,	transp,	transp,	transp,	transp,	
	transp,	transp,	
ctrlR/**/,	transp,	transp,	
	transp,	transp,	transp	
),


// layer 2 -- Qwerty Windows layer
  MATRIX_LAYER(
	// unused
	K, nop,	
	// left hand
	transp,	transp,	transp,	transp,	transp,	transp,	transp,	
	transp,	q,	w,	e,	r,	t,	transp,	
	transp,	a,	s,	d,	f,	g,
	transp,	z,	x,	c,	v,	b,	guiL,
	transp,	transp,	transp,	transp,	transp,	
	        transp,	transp,	
	transp,	transp,	ctrlL,
	transp,	transp,	transp,
	// right hand
	transp,	transp,	transp,	transp,	transp,	transp,	transp,	
	transp,	y,	u,	i,	o,	p,	transp,	
	        h,	j,	k,	l,	semicol, transp,	
	guiR,   n,	m,	comma,	period,	transp,	slash,	
	                transp,	transp,	transp,	transp,	transp,	
	transp,	transp,	
        ctrlR,	transp,	transp,	
	transp,	transp,	transp	
),

// layer 3 -- Numbers & Functions
    MATRIX_LAYER(
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     nop,       F1,       F2,       F3,       F4,       F5,       F6,
     nop,       F7,       F8,       F9,      F10,      F11,      F12,
     nop,      nop,     mmute,  mvold,  mvolu,      nop,
     nop,    mstop,    mprev,    mplay,    mnext,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                    transp,      transp,
                                                       transp,      transp,      transp,
                                                       transp,      transp,      transp,
// right hand ..... ......... ......... ......... ......... ......... .........
               ins,      nop,      nop,    equal,    kpDiv,    kpMul,      nop,
               num,      nop,      kp7,      kp8,      kp9,    kpSub,      nop,
                         nop,      kp4,      kp5,      kp6,    kpAdd,      nop,
               nop,      nop,      kp1,      kp2,      kp3,  kpEnter,      nop,
                                   nop,      nop,    kpDec,  kpEnter,      nop,
     transp,      transp,
     transp,      transp,      transp,
     transp,      transp,      kp0  ),


// layer 4 -- Dev & Vim shortcuts
    MATRIX_LAYER(
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,   parenL,   parenR,      nop,      nop,
     nop,    equal,     plus,   braceL,   braceR,   exclam,
     nop,     dash,  undersc,    brktL,    brktR,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                    transp,      transp,
                                                       transp,      transp,      transp,
                                                       transp,      transp,      transp,
// right hand ..... ......... ......... ......... ......... ......... .........
               nop,      nop,      nop,      nop,      nop,      nop,    LHadm,
               nop,    caret,      nop,      nop,   dollar,      nop,      nop,
                           h,        j,        k,        l,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                                   nop,      nop,      nop,      nop,      nop,
     transp,      transp,
     transp,      transp,      transp,
     transp,      transp,      transp  ),

// layer 5 -- Admin
    MATRIX_LAYER(
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
   btldr,      nop,      nop,      nop,    LTqwe,    LTwin,    LBase,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                    nop,nop,
                                                       nop,nop,nop,
                                                       nop,nop,nop,
// right hand ..... ......... ......... ......... ......... ......... .........
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                         nop,      nop,      nop,      nop,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                                   nop,      nop,      nop,      nop,      nop,
     nop,nop,
     nop,nop,nop,
     nop,nop,      transp  ),






//////////////////////////////////////////////////////////////////////////////
// ORIGINAL VERSIONS OF STUFF


    MATRIX_LAYER(  // layer 0 : default (colemak)
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
   equal,        1,        2,        3,        4,        5,   lpu2l2,
     tab,        q,        w,        f,        p,        g,      esc,
   ctrlL,        a,        r,        s,        t,        d,
shL2kcap,        z,        x,        c,        v,        b, lpupo2l2,
    guiL,    grave,  bkslash,     altL, lpupo1l1,
                                                               ctrlL,     altL,
                                                       nop,      nop,     home,
                                                     space,    enter,      end,
// right hand ..... ......... ......... ......... ......... ......... .........
           numPush,        6,        7,        8,        9,        0,     dash,
               esc,        j,        l,        u,        y,  semicol,  bkslash,
                           h,        n,        e,        i,        o,    quote,
           numPuPo,        k,        m,    comma,   period,    slash, shR2kcap,
                              lpupo1l1,   arrowL,   arrowD,   arrowU,   arrowR,
    altR,    ctrlR,
   pageU,      nop,      nop,
   pageD,      del,       bs  ),

// ............................................................................

    MATRIX_LAYER(  // layer 1 : function and symbol keys
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,       F1,       F2,       F3,       F4,       F5,      F11,
  transp,   braceL,   braceR,    brktL,    brktR,    colon,   transp,
  transp,  bkslash,    slash,   parenL,   parenR,  semicol,
  transp,   exclam,       at,    pound,   dollar,  percent,   transp,
  transp,   transp,   transp,   transp, lpupo3l3,
                                                              transp,   transp,
                                                    transp,   transp,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
               F12,       F6,       F7,       F8,       F9,      F10,    power,
            transp,      nop,    equal,     plus,     dash,  undersc,      nop,
                      arrowL,   arrowD,   arrowU,   arrowR,      nop,      nop,
            transp,    caret,      amp, asterisk,   parenL,   parenR,   transp,
                              lpupo3l3,   transp,   transp,   transp,   transp,
  transp,   transp,
  transp,   transp,   transp,
  transp,   transp,   transp  ),

// ............................................................................

    MATRIX_LAYER(  // layer 2 : QWERTY alphanum
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,        1,        2,        3,        4,        5,   lpo2l2,
  transp,        q,        w,        e,        r,        t,   transp,
  transp,        a,        s,        d,        f,        g,
  transp,        z,        x,        c,        v,        b,   transp,
  transp,   transp,   transp,   transp,   transp,
                                                              transp,   transp,
                                                    transp,   transp,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            transp,        6,        7,        8,        9,        0,   transp,
            transp,        y,        u,        i,        o,        p,   transp,
                           h,        j,        k,        l,  semicol,   transp,
            transp,        n,        m,    comma,   period,    slash,   transp,
                                transp,   transp,   transp,   transp,   transp,
  transp,   transp,
  transp,   transp,   transp,
  transp,   transp,   transp  ),


// ............................................................................

    MATRIX_LAYER(  // layer 3 : keyboard functions
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
   btldr,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                 nop,      nop,
                                                       nop,      nop,      nop,
                                                       nop,      nop,      nop,
// right hand ..... ......... ......... ......... ......... ......... .........
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                         nop,      nop,      nop,      nop,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                                   nop,      nop,      nop,      nop,      nop,
     nop,      nop,
     nop,      nop,      nop,
     nop,      nop,      nop  ),

// ............................................................................

    MATRIX_LAYER(  // layer 4 : numpad
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,      ins,   transp,   transp,   transp,
                                                              transp,   transp,
                                                    transp,   transp,   transp,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            numPop,   transp,   numPop,    equal,    kpDiv,    kpMul,   transp,
            transp,   transp,      kp7,      kp8,      kp9,    kpSub,   transp,
                      transp,      kp4,      kp5,      kp6,    kpAdd,   transp,
            transp,   transp,      kp1,      kp2,      kp3,  kpEnter,   transp,
                                transp,   transp,   period,  kpEnter,   transp,
  transp,   transp,
  transp,   transp,   transp,
  transp,   transp,      kp0  ),

// ............................................................................
};
