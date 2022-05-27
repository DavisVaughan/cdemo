x <- my_fun(1:5)
x <- my_fun(.GlobalEnv) # Yes, anything!

# Nice!
x <- c(1, 3, 5)
times_two_bad(x)

# But, goes against the golden rule of R
x

# And not particularly nice
x <- c(1L, 3L, 5L)
times_two_bad(x)

# Nice!
x <- c(1, 3, 5)
times_two(x)
x

x <- c(1L, 3L, 5L)
times_two(x)

# How bad? Uncomment the line below and run it a few times.
x <- rep(1, 1e6)
# times_two_no_protect(x)










