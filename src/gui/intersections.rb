# -*- coding: utf-8 -*-
#
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

# Public: Inicializa la ventana y variables de processing
#

def setup
  background 255, 255, 255
  size(600, 400,P2D)
  # Conjunto de segmentos de prueba
  @half_edges = [[[1,1],[2,7]],
                 [[3,3],[1,8]],
                 [[1,13],[5,15]],
                 [[6,5],[10,11]],
                 [[7,3],[18,8]],
                 [[11,1],[15,14]],
                 [[10,11],[15,4]],
                 [[18,12],[21,1]]]

  
  @zoom = 25
  
  @half_edges = @half_edges.map do |segment|

     [segment[0].map{|point| point * @zoom},
      segment[1].map{|point| point * @zoom}]    
  end
  draw_intersections
end

# Public: Dibuja el conjunto de puntos de la interseccion de @half_edges
#
# Esta funcion la debes de modificar para que dibuje los puntos
def draw_intersections

  # Dibuja los segmentos y sus puntos finales.
  @half_edges.each do
    |segment|
    start = segment[0]
    ending = segment[1]
    
    ellipse(start[0].to_f, start[1].to_f,5.0,5.0)
    ellipse(ending[0].to_f, ending[1].to_f, 5.0, 5.0)

    line(start[0].to_f, start[1].to_f, ending[0].to_f, ending[1].to_f)
  end
  
  # Calcula la interseccion de segmentos a partir de la funcion que debes de
  # completar.
  intersections = construct_intersections

  #
  # Aqui van tu codigo
  # Debes de dibujar los puntos de la interseccion.
  #
  
end

# Public: Convierte los segmentos @half_edges a segmentos de C, calcula la intersecion
#         con la funcion de C y regresa un arreglo de puntos de Ruby.
#         Un punto esta compuesto por [x,y] donde 'x' y 'y' son las
#         coordenadas del punto de intersección.
#
def construct_intersections
  require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/intersection"))
  
  segments = @half_edges.clone

  points = segments.map {
    |segment|
    [Points.init_point(segment[0][0],segment[0][1]),
     Points.init_point(segment[1][0],segment[1][1])]
  }
  
  half_edges = points.map{
    |segment| 
    HalfEdge.init_half_edge(segment[0],segment[1])
  }
  
  list = List.init_double_linked_list(List::Item_type[:half_edge])
  
  half_edges.each do |segment|
    List.push_back(list,segment)
  end
  
  intersections = Intersection.find_intersections(list)

  if not(intersections.null?)
    intersections_ruby = List.to_a(intersections) 
    
    return intersections_ruby
    
  else
    return []
  end
  
end
