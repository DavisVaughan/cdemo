my_fun <- function(x) {
  .Call(c_my_fun, x)
}

times_two <- function(x) {
  .Call(c_times_two, x)
}
