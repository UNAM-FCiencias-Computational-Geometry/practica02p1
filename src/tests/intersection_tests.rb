# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/intersection"))
require File.expand_path(File.join(File.dirname(__FILE__), "half_edge_tests"))


#
# Reabre el modulo de Test para agregar las clase TestIntersection, la cual
# tiene los test de las funciones de la estructura de C.
#
module Test

  # Public: Es una clase que representa un segmento.
  # 
  # Examples
  #       
  #        Test::Segment.new([1,2],[2,3])
  # 

  class Segment
    attr_accessor :start, :ending
    def initialize(start,ending)
      @start = start
      @ending = ending
    end

    # Public: Calcula la intersecion del segmento con el otro que se le pase.
    #
    # Regresa el objeto de C que representa el punto de interseccion.
    def intersection(another_segment)
      return TestHalfEdge.he_intersection(@start,@ending,another_segment.start,
                                          another_segment.ending)
    end
    
  end

  class TestIntersection

    # Public: Prueba la funcion de interseccion cuando se le pasa un nulo.
    #
    # Examples
    #
    #     Test::TestIntersection.null_intersection
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.null_intersection
      set_of_intersections = Intersection.find_intersections(nil)
      
      result = set_of_intersections.null?

      result      
    end

    # Public: Prueba la funcion de interseccion cuando se le pasa una lista de segmentos
    #         vacía.
    #
    # Examples
    #
    #     Test::TestIntersection.empty_set
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.empty_set
      
      list = List.init_double_linked_list(List::Item_type[:half_edge])

      set_of_intersections = Intersection.find_intersections(list)

      first_point = List.pop_front(set_of_intersections)

      return false if set_of_intersections.null?

      result = first_point.null?

      List.destroy_double_linked_list(list)
      List.destroy_double_linked_list(set_of_intersections)

      result
    end

    # Public: Calcula la interseccion de segmentos de Ruby, no los de C.
    #
    # Un arreglo de Ruby que contiene los puntos de Ruby que forman la interseccion.
    #
    def self.find_intersections(half_edges)
      intersection_set = []
      half_edges = half_edges.clone
      while half_edges.first != nil 
        segment_a = half_edges.pop
        half_edges.reverse.each do |segment_b|
        
           a = Segment.new(segment_a[0], segment_a[1])
           b = Segment.new(segment_b[0], segment_b[1])

           point_intersection = a.intersection(b)

           if not(point_intersection.nil?) then
             intersection_set << point_intersection
           end
         end
      end
       
       intersection_set
     end
   
    # Public: Prueba la funcion de interseccion cuando se le pasa una lista de segmentos
    #         no vacia
    #
    # Examples
    #
    #     Test::TestIntersection.not_empty_set
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.not_empty_set

      l1 = [[0,0],[1,6]].map{|x| [x[0].to_f,x[1].to_f]}
      l2 = [[2,2],[0,7]].map{|x| [x[0].to_f,x[1].to_f]}
      l3 = [[0,12],[4,14]].map{|x| [x[0].to_f,x[1].to_f]}
      l4 = [[5,4],[9,10]].map{|x| [x[0].to_f,x[1].to_f]}
      l5 = [[6,2],[17,7]].map{|x| [x[0].to_f,x[1].to_f]}
      l6 = [[10,-1],[14,13]].map{|x| [x[0].to_f,x[1].to_f]}
      l7 = [[9,10],[14,3]].map{|x| [x[0].to_f,x[1].to_f]}
      l8 = [[17,11],[20,0]].map{|x| [x[0].to_f,x[1].to_f]}
      
      raw_half_edges = [l1,l2,l3,l4,l5,l6,l7,l8]
      raw_intersections = find_intersections(raw_half_edges)
      
      
      points = raw_half_edges.map{|x| [Points.init_point(x[0][0],x[0][1]),
                                       Points.init_point(x[1][0],x[1][1])]}
      
      half_edges = points.map {|x| HalfEdge.init_half_edge(x[0],x[1])}
      
      list = List.init_double_linked_list(List::Item_type[:half_edge])
      
      half_edges.each do |x|
        List.push_back(list,x)
      end
      
      intersections = Intersection.find_intersections(list)       
      
      return false if (intersections.null?)
      
      result = compare_intersections(raw_intersections,List.to_a(intersections))
      
      List.destroy_double_linked_list(list)
      List.destroy_double_linked_list_with_types(intersections)
      
      result
    end
    
    # Public: Recibe dos arreglos de puntos de interseccion de Ruby y regrsa true si son iguales
    #         false en otro caso. Estos arreglos de puntos son las interseccopmes calculadas
    #         por Ruby y por C, no importa el orden en que las intersecciones son dadas.
    #
    def self.compare_intersections(raw,process)
      
      return false if (raw.size != process.size)
      
      raw.each do |point|
        array = process.clone
        
        array.keep_if { |x| 
          
          ((x[2] == point[2] and x[3] == point[3]) or
           (x[2] == point[3] and x[3] == point[2])) and
          (x[0] <= point[0] + 0.001 and x[0] >= point[0] - 0.001) and
          (x[1] <= point[1] + 0.001 and x[1] >= point[1] - 0.001)
        }
        
        return false if (array.size != 1)
        
      end
      
      return true
    end
    
  end
end
