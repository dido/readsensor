#!/usr/bin/env ruby
# coding: utf-8
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
require 'net/http'

SERVER = "YOUR-SERVER-HERE"
RRDPATH = "PATH-TO-GENERATED-RRDS"
RRDTOOL = "/usr/bin/rrdtool"

str = Net::HTTP.get(SERVER, "/");
temp, hum, hidx, atm, alt = str.split(":")
system("#{RRDTOOL} update #{File.join(RRDPATH, 'temperature.rrd')} N:#{temp}")
system("#{RRDTOOL} update #{File.join(RRDPATH, 'humidity.rrd')} N:#{hum}")
system("#{RRDTOOL} update #{File.join(RRDPATH, 'heatindex.rrd')} N:#{hidx}")
system("#{RRDTOOL} update #{File.join(RRDPATH, 'pressure.rrd')} N:#{atm}")
