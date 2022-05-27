my_fun <- function(x) {
  .Call(c_my_fun, x)
}

times_two_bad <- function(x) {
  .Call(c_times_two_bad, x)
}

times_two <- function(x) {
  .Call(c_times_two, x)
}

times_two_no_protect <- function(x) {
  .Call(c_times_two_no_protect, x)
}
