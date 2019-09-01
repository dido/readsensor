#!/bin/sh
# Copyright © 2019 Rafael R. Sevilla
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
RRDTOOL=/usr/bin/rrdtool
$RRDTOOL create temperature.rrd --step 300 \
  DS:temp:GAUGE:600:-273:5000 \
  RRA:AVERAGE:0.5:1:2016 \
  RRA:MIN:0.5:12:8766 \
  RRA:MAX:0.5:12:8766 \
  RRA:AVERAGE:0.5:12:8766
$RRDTOOL create humidity.rrd --step 300 \
  DS:hum:GAUGE:600:0:100 \
  RRA:AVERAGE:0.5:1:2016 \
  RRA:MIN:0.5:12:8766 \
  RRA:MAX:0.5:12:8766 \
  RRA:AVERAGE:0.5:12:8766
$RRDTOOL create heatindex.rrd --step 300 \
  DS:heatindex:GAUGE:600:-273:5000 \
  RRA:AVERAGE:0.5:1:2016 \
  RRA:MIN:0.5:12:8766 \
  RRA:MAX:0.5:12:8766 \
  RRA:AVERAGE:0.5:12:8766
$RRDTOOL create pressure.rrd --step 300 \
  DS:pressure:GAUGE:600:100:1500 \
  RRA:AVERAGE:0.5:1:2016 \
  RRA:MIN:0.5:12:8766 \
  RRA:MAX:0.5:12:8766 \
