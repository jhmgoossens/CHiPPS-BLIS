/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Common Public License as part of the        *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors: Yan Xu, SAS Institute Inc.                                       *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           * 
 *                                                                           *
 * Copyright (C) 2001-2006, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

#include "BlisMessage.h"

//#############################################################################

typedef struct {
    BLIS_Message internalNumber;
    int externalNumber;              // or continuation
    char detail;
    const char * message;
} Blis_message;

//#############################################################################

static Blis_message us_english[]=
{
    {BLIS_S_VERSION, 1, 1, "BLIS version 0.6"},
    {BLIS_PEAK_MEMORY, 10, 1, "Peak memory usage: %.2f M"},
    {BLIS_W_LP, 20, 1, "WARNING: The Problem does not have integer variables"},
    {BLIS_ROOT_PROCESS, 30, 1, "Processing the root node"},
    {BLIS_ROOT_TIME, 35, 1, "Solving the root relaxation took %.2f seconds CPU time"},
    {BLIS_DUMMY_END, 999999, 0, ""}
};

//#############################################################################

/* Constructor */
BlisMessage::BlisMessage(Language language) 
    :
    CoinMessages(sizeof(us_english) / sizeof(Blis_message))
{
    language_ = language;
    strcpy(source_, "Blis");
    Blis_message * message = us_english;

    while (message->internalNumber != BLIS_DUMMY_END) {
	CoinOneMessage oneMessage(message->externalNumber, message->detail,
				  message->message);
	addMessage(message->internalNumber, oneMessage);
	message++;
    }

    // now override any language ones

    switch (language) {

    default:
	message = NULL;
	break;
    }

    // replace if any found
    if (message) {
	while (message->internalNumber != BLIS_DUMMY_END) {
	    replaceMessage(message->internalNumber, message->message);
	    message++;
	}
    }
}
