BEGIN {
  maxw = -1
  maxr = -1
  w_count = 0
  r_count = 0
  rw_violations = 0
  ww_violations = 0
}

{
  # TODO
  ## Your code here
  ## Hint: Add in code to update variables for the check below
  if ($0 == "sr") r_count++;
  if ($0 == "dr") r_count--;
  if ($0 == "sw") w_count++;
  if ($0 == "dw") w_count--;

  if (r_count > maxr) {
    maxr = r_count
  }
  if (w_count > maxw) {
    maxw = w_count
  }
  

  # Tests to see if everything is fine
  ## test for concurrent writer and reader
  if (w_count > 0 && r_count > 0) {
    rw_violations++ 
   }

  ## test for concurrent writers
  if (w_count > 1) {
    ww_violations++
  }
}     

END {
  print "maxr = "maxr", maxw = "maxw  
  if (rw_violations == 0) {
    print "reader/writer test: PASS"
  } else {
    print "reader/writer test: FAIL"
  } 
  if (ww_violations == 0) {
    print "writer/writer test: PASS"
  } else {
    print "writer/writer test: FAIL"
  } 
}

