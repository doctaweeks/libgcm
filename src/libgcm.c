#include "libgcm.h"

#include <string.h>
#if DEBUG
#include <stdio.h>
#endif

#define GCM_URL "https://android.googleapis.com/gcm/send"

static const char *gcm_type_internal[] = {
	"deleted_messages",
	"gcm",
	"send_error"
};

int libgcm_init(struct gcm *g, const char sender[GCM_KEY_LEN])
{
	if (!g)
		return -1;

	curl_global_init(CURL_GLOBAL_ALL);
	g->curl = curl_easy_init();

	curl_easy_setopt(g->curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V6);
	curl_easy_setopt(g->curl, CURLOPT_URL, GCM_URL);

	snprintf(g->auth, GCM_KEY_LEN + 19, "Authorization:key=%s", sender);

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
	json_object_object_add(body, "delay_while_idle", json_object_new_boolean(0));
	json_object_object_add(body, "time_to_live", json_object_new_int(43200));
	//json_object_object_add(body, "dry_run", json_object_new_boolean(1));

	const char *body_str = json_object_to_json_string(body);

	curl_easy_setopt(g->curl, CURLOPT_POSTFIELDS, body_str);
	curl_easy_setopt(g->curl, CURLOPT_HTTPHEADER, g->headerlist);

	CURLcode res = curl_easy_perform(g->curl);

	if(res != CURLE_OK) {
#if DEBUG
	fprintf(stderr, "POST failed: %s\n",
		              curl_easy_strerror(res));
#endif
		ret = -1;
	}

	json_object_put(body);

	return ret;
}

int libgcm_send_simple(struct gcm *g, const char *message, const struct regid regids[])
{
	return libgcm_send_json(g, json_object_new_string(message), regids);
}
