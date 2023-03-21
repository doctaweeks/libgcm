#ifndef LIBGCM_H_
#define LIBGCM_H_

#include <curl/curl.h>
#include <json-c/json.h>

#define GCM_KEY_LEN 4096
#define GCM_REGID_MAX 4096

#define GCM_KEY_PREFIX_LEN 19

struct gcm {
	char auth[GCM_KEY_PREFIX_LEN + GCM_KEY_LEN];

	CURL *curl;
	struct curl_slist *headerlist;

	CURLcode last_result;
	long last_http_code;
};

struct regid {
	char id[GCM_REGID_MAX+1];
};

int libgcm_init(struct gcm *g, const char sender[GCM_KEY_LEN]);
int libgcm_cleanup(struct gcm *g);

int libgcm_send_simple(struct gcm *g, const char *message, const struct regid regids[]);
int libgcm_send_json(struct gcm *g, struct json_object *j, const struct regid regids[]);

const char *libgcm_get_last_strerror(struct gcm *g);

#endif
