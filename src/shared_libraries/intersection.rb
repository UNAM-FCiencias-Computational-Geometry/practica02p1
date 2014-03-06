# -*- coding: utf-8 -*-
#
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/double_linked_list"))
require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/half_edge"))
require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/points"))

#
# Modulo para mapear la funcion de interseccion de puntos de C a Ruby.
#
module Intersection
  extend FFI::Library
  ffi_lib "lib/libintersection.so"

  attach_function :find_intersections, [List::List.by_ref], List::List.by_ref
  
end
