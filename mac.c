/* $Id:$ */
/* Copyright 2004 Aaron Turner 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright owners nor the names of its
 *    contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "config.h"
#include "defines.h"
#include "mac.h"

/*
 * converts a string representation of a MAC address, based on 
 * non-portable ether_aton() 
 */
void
mac2hex(const char *mac, char *dst, int len)
{
    int i;
    long l;
    char *pp;

    if (len < 6)
        return;

    while (isspace(*mac))
        mac++;

    /* expect 6 hex octets separated by ':' or space/NUL if last octet */
    for (i = 0; i < 6; i++) {
        l = strtol(mac, &pp, 16);
        if (pp == mac || l > 0xFF || l < 0)
            return;
        if (!(*pp == ':' || (i == 5 && (isspace(*pp) || *pp == '\0'))))
            return;
        dst[i] = (u_char) l;
        mac = pp + 1;
    }
}

/*
 * converts a string representation of TWO MAC addresses, which
 * are comma deliminated into two hex values.  Either *first or *second 
 * can be NULL if there is nothing before or after the comma.
 */
void
dualmac2hex(const char *dualmac, char *first, char *second, int len)
{
    char *tok, *temp;
    
    /* if we've only got a comma, then return NULL's */
    if (len <= 1) {
        second = first = NULL;
        return;
    }

        
    temp = strtok_r(dualmac, ',', &tok);
    mac2hex(temp, first, len);

    temp = strtok_r(NULL, ',', &tok);
    mac2hex(temp, second, len);

    return;

}


/*
  Local Variables:
  mode:c
  indent-tabs-mode:nil
  c-basic-offset:4
  End:
*/
