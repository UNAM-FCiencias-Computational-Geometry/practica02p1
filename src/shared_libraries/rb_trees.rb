# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__),"points"))

#
# Modulo para mapear los rb-tree de C a Ruby, junto con sus funciones.
#
module RBTree
  extend FFI::Library
  ffi_lib "lib/librb_tree.so"

  Compare_by = enum( :x, 1,
                     :y)

  class Tree < FFI::Struct
    layout :root, :pointer,
           :coordinate, Compare_by
           
  end

  attach_function :init_rb_tree, [Compare_by], Tree.by_ref
  attach_function :destroy_rb_tree, [Tree.by_ref], :void

  attach_function :rb_insert, [Tree.by_ref, Points::Point.by_ref], :void
  attach_function :rb_search, [Tree.by_ref, Points::Point.by_ref], Points::Point.by_ref
  attach_function :rb_delete, [Tree.by_ref, Points::Point.by_ref], Points::Point.by_ref
  
  attach_function :rb_min, [Tree.by_ref], Points::Point.by_ref
  attach_function :rb_max, [Tree.by_ref], Points::Point.by_ref

end

