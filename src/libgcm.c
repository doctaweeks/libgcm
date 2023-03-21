#include "libgcm.h"

#include <string.h>
#if DEBUG
#include <stdio.h>
#endif

#define GCM_URL "https://fcm.googleapis.com/fcm/send"

static size_t write_cb(void *data, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}

int libgcm_init(struct gcm *g, const char sender[GCM_KEY_LEN])
{
	if (!g)
		return -1;

	curl_global_init(CURL_GLOBAL_ALL);
	g->curl = curl_easy_init();

	curl_easy_setopt(g->curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V6);
	curl_easy_setopt(g->curl, CURLOPT_URL, GCM_URL);
	curl_easy_setopt(g->curl, CURLOPT_FAILONERROR, 1);

	curl_easy_setopt(g->curl, CURLOPT_CONNECTTIMEOUT_MS, 500);
	curl_easy_setopt(g->curl, CURLOPT_TIMEOUT_MS, 1500);

	curl_easy_setopt(g->curl, CURLOPT_WRITEFUNCTION, write_cb);

	snprintf(g->auth, GCM_KEY_PREFIX_LEN + GCM_KEY_LEN, "Authorization:key=%s", sender);

	g->headerlist = NULL;
	g->headerlist = curl_slist_append(g->headerlist, "Content-Type:application/json");
	g->headerlist = curl_slist_append(g->headerlist, g->auth);

	return 0;
}

int libgcm_cleanup(struct gcm *g)
{
	curl_slist_free_all(g->headerlist);
	curl_easy_cleanup(g->curl);
	curl_global_cleanup();

	return 0;
}

static struct json_object *_build_id_array(const struct regid regids[]) {
	struct json_object *id_array = json_object_new_array();
	const struct regid *id = regids;

	while (id->id[0]) {
#if DEBUG
		printf("Adding %s\n", id->id);
#endif
		json_object_array_add(id_array, json_object_new_string(id->id));
		id++;
	}

	return id_array;
}

int libgcm_send_json(struct gcm *g, struct json_object *j, const struct regid regids[])
{
	int ret = 0;
	struct json_object *id_array = _build_id_array(regids);

	struct json_object *body = json_object_new_object();
	json_object_object_add(body, "registration_ids", id_array);
	json_object_get(j);
	json_object_object_add(body, "data", j);

	//json_object_object_add(body, "collapse_key", j);
	json_object_object_add(body, "time_to_live", json_object_new_int(43200));
	json_object_object_add(body, "priority", json_object_new_string("high"));
	//json_object_object_add(body, "dry_run", json_object_new_boolean(1));

	const char *body_str = json_object_to_json_string(body);

	curl_easy_setopt(g->curl, CURLOPT_POSTFIELDS, body_str);
	curl_easy_setopt(g->curl, CURLOPT_HTTPHEADER, g->headerlist);

	g->last_result = curl_easy_perform(g->curl);
	curl_easy_getinfo(g->curl, CURLINFO_RESPONSE_CODE, &g->last_http_code);

	if(g->last_result != CURLE_OK) {
		ret = -1;
	}

	json_object_put(body);

	return ret;
}

int libgcm_send_simple(struct gcm *g, const char *message, const struct regid regids[])
{
	return libgcm_send_json(g, json_object_new_string(message), regids);
}

const char *libgcm_get_last_strerror(struct gcm *g)
{
	return curl_easy_strerror(g->last_result);
}
