#!/bin/bash
exec docker compose run --entrypoint "" -iT --rm writer bin/validation-tool "$@"
