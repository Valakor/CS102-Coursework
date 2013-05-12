graph [
  #comment "This is a test graph"
  directed 1
  node [ 
    id 0
    name "User A"
    age 0
    zip 90018
  ]
  node [ 
    id 1
    name "User B"
    age 1
    zip 90007
  ]
  node [ 
    id 2
    name "User C"
    age 2
    zip 90210
  ]
  node [ 
    id 3
    name "User D"
    age 3
    zip 20500
  ]
  node [ 
    id 4
    name "User E"
    age 4
    zip 20500
  ]
  node [ 
    id 5
    name "User F"
    age 5
    zip 20500
  ]
  edge [
   source 0
   target 2
  ]
  edge [
   source 2
   target 0
  ]
  edge [
   source 1
   target 2
  ]
  edge [
   source 2
   target 1
  ]
  edge [
   source 2
   target 3
  ]
  edge [
   source 3
   target 2
  ]
  edge [
   source 4
   target 3
  ]
  edge [
   source 3
   target 4
  ]
  edge [
   source 5
   target 3
  ]
  edge [
   source 3
   target 5
  ]
]
