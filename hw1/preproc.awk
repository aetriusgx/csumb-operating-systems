{
  if (substr($1,1,2) == "#@") {
    printf("\n%s", $2)
  }
  if (substr($1,1,1) != "#") {
    gsub(" |\t","",$0)    # strip whitespace
    printf(" %s", $0)
  }
}
END {
  printf("\n")
}
