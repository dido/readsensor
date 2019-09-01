<?php
/* Copyright © 2019 Rafael R. Sevilla

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
header("Pragma: public");
header("Expires: 0");
header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
header("Cache-Control: private",false);
header("Content-Type: image/png");
header("Content-Transfer-Encoding: binary"); 
$width=640;
$height=240;
if (array_key_exists("start", $_GET)) {
  $startdate = $_GET["start"];
} else {
  $startdate = 86400;
}

if (!settype($startdate, "integer")) {
  $startdate = 86400;
}
if (array_key_exists("graph", $_GET)) {
  $ngraph = $_GET["graph"];
} else {
  $ngraph = 0;
}

if ($ngraph < 0 || $ngraph > 3) {
  $ngraph = 0;
}

$graphs = array(array("/home/dido/rrd/temperature.rrd", "temp", "Temperature (°C)"),
		array("/home/dido/rrd/humidity.rrd", "hum", "Relative Humidity %"),
		array("/home/dido/rrd/heatindex.rrd", "heatindex", "Heat Index (°C)"),
		array("/home/dido/rrd/pressure.rrd", "pressure", "Atmospheric Pressure (hPa)"));
$graph = $graphs[$ngraph];
if ($ngraph == 0) {
	system("rrdtool graph - --vertical-label='°C' \
		--width {$width} --height={$height} \
		--start -{$startdate} \
		DEF:temp={$graphs[0][0]}:temp:AVERAGE \
		DEF:heatindex={$graphs[2][0]}:heatindex:AVERAGE \
		LINE1:temp\#00FF00:'Temperature (°C)' \
		GPRINT:temp:LAST:'Current\:%.1lf°C' \
		GPRINT:temp:MIN:'Minimum\:%.1lf°C' \
		GPRINT:temp:MAX:'Maximum\:%.1lf°C\\n' \
		LINE2:heatindex\#FF0000:'Heat Index (°C)' \
		GPRINT:heatindex:LAST:'Current\:%.1lf°C' \
		GPRINT:heatindex:MIN:'Minimum\:%.1lf°C' \
		GPRINT:heatindex:MAX:'Maximum\:%.1lf°C\\n'");
} else if ($ngraph == 3) {
	system("rrdtool graph - --alt-y-grid --alt-autoscale \
		--vertical-label=hPa --units-exponent 0 \
		--width ${width} --height {$height} --start -{$startdate} \
		DEF:pressure={$graphs[3][0]}:pressure:AVERAGE \
		LINE1:pressure\#0000FF:'Atmospheric Pressure (hPa)' \
		GPRINT:pressure:LAST:'Current\:%.1lf' \
		GPRINT:pressure:MIN:'Minimum\:%.1lf' \
		GPRINT:pressure:MAX:'Maximum\:%.1lf\\n'");
} else {
	system("rrdtool graph - --width {$width} --height={$height} \
		--start -{$startdate} \
		DEF:{$graph[1]}={$graph[0]}:{$graph[1]}:AVERAGE \
		LINE1:{$graph[1]}\#00FF00:'{$graph[2]}' \
		GPRINT:{$graph[1]}:LAST:'Current\:%.1lf' \
		GPRINT:{$graph[1]}:MIN:'Minimum\:%.1lf' \
		GPRINT:{$graph[1]}:MAX:'Maximum\:%.1lf\\n'");
}
?>
