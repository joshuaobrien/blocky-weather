#!/bin/bash

API_KEY="APPID=SUPERSECRET"
BASE_URL="http://api.openweathermap.org/data/2.5/weather?"
CITY_QUERY="q=Brisbane"
AMPERSAND="&"

raw=$(curl -s $BASE_URL$CITY_QUERY$AMPERSAND$API_KEY)

(ruby -rjson -e "out = JSON.parse('${raw}'); puts out['weather'][0]['main']") | figlet


