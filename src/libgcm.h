#ifndef _LIBGCM_H_
#define _LIBGCM_H_

#include <curl/curl.h>
#include <json-c/json.h>

#define GCM_KEY_LEN 40

struct gcm {
	char auth[GCM_KEY_LEN + 19];

	CURL *curl;
	struct curl_slist *headerlist;
};

struct regid {
	const char id[256];
};

int libgcm_init(struct gcm *g, const char sender[GCM_KEY_LEN]);
int libgcm_cleanup(struct gcm *g);

int libgcm_send_simple(struct gcm *g, const char *message, const struct regid regids[]);
int libgcm_send_json(struct gcm *g, struct json_object *j, const struct regid regids[]);

#endif
