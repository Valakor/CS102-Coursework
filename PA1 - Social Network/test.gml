graph [
  #comment "This is a test graph"
  directed 1
  node [ 
    id 0
    name "Mark Redekopp"
    age 34
    zip 90018
  ]
  node [ 
    id 1
    name "Tommy Trojan"
    age 124
    zip 90007
  ]
  node [ 
    id 2
    name "Max Nikias"
    age 65
    zip 90210
  ]
  node [ 
    id 3
    name "Barack Obama"
    age 51
    zip 20500
  ]
  edge [
   source 0
   target 1
  ]
  edge [
   source 1
   target 0
  ]
  edge [
   source 0
   target 2
  ]
  edge [
   source 2
   target 0
  ]
]
