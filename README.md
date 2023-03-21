libgcm can be used add Google Cloud Messaging (GCM) to an application. It
currently supports a simple send function to one or more clients.

Default timeouts can be changed at compile time:

    ./configure CPPFLAGS="-DGCM_TIMEOUT_MS=2000 -DGCM_CONNECTTIMEOUT_MS=800"

Changing `CPPFLAGS` this way will not trigger recompilation the next time
`make` is run; `make clean` before `make` is necessary when changing these
flags.
