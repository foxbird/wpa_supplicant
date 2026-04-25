/*
 * WPA Supplicant - ASCII passphrase to WPA PSK tool
 * Copyright (c) 2003-2005, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "includes.h"
#ifndef _WIN32
#include <termios.h>
#endif /* _WIN32 */

#include "common.h"
#include "crypto/sha1.h"


int main(int argc, char *argv[])
{
#ifndef _WIN32
	struct termios term;
#endif /* _WIN32 */
	unsigned char psk[32];
	int i;
	char *ssid, *passphrase, buf[64], *pos;
	size_t len;

	if (argc < 2) {
		printf("usage: wpa_passphrase <ssid> [passphrase]\n"
			"\nIf passphrase is left out, it will be read from "
			"stdin\n");
		return 1;
	}

	ssid = argv[1];

	if (argc > 2) {
		passphrase = argv[2];
	} else {
		bool ctrl_echo;

		fprintf(stderr, "# reading passphrase from stdin\n");
#ifndef _WIN32
		if (tcgetattr(STDIN_FILENO, &term) < 0) {
			perror("tcgetattr");
			return 1;
		}
		ctrl_echo = term.c_lflag & ECHO;
		term.c_lflag &= ~ECHO;
		if (ctrl_echo && tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0) {
			perror("tcsetattr:error disabling echo");
			return 1;
		}
#else /* _WIN32 */
		ctrl_echo = 0;
#endif /* _WIN32 */
		if (fgets(buf, sizeof(buf), stdin) == NULL) {
			fprintf(stderr, "Failed to read passphrase\n");
			return 1;
		}
#ifndef _WIN32
		term.c_lflag |= ECHO;
		if (ctrl_echo && tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0) {
			perror("tcsetattr:error enabling echo");
			return 1;
		}
#endif /* _WIN32 */
		buf[sizeof(buf) - 1] = '\0';
		pos = buf;
		while (*pos != '\0') {
			if (*pos == '\r' || *pos == '\n') {
				*pos = '\0';
				break;
			}
			pos++;
		}
		passphrase = buf;
	}

	len = os_strlen(passphrase);
	if (len < 8 || len > 63) {
		fprintf(stderr, "Passphrase must be 8..63 characters\n");
		return 1;
	}
	if (has_ctrl_char((u8 *) passphrase, len)) {
		fprintf(stderr, "Invalid passphrase character\n");
		return 1;
	}

	if (pbkdf2_sha1(passphrase, (u8 *) ssid, os_strlen(ssid), 4096, psk, 32)
	    != 0) {
		fprintf(stderr, "Error in pbkdf2_sha1()\n");
		return 1;
	}

	printf("network={\n");
	printf("\tssid=\"%s\"\n", ssid);
	printf("\t#psk=\"%s\"\n", passphrase);
	printf("\tpsk=");
	for (i = 0; i < 32; i++)
		printf("%02x", psk[i]);
	printf("\n");
	printf("}\n");

	return 0;
}
