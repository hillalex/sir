test_that("can run model with defaults", {
  expect_silent(run_model(1:100))
})

test_that("can run model with named params", {
  expect_silent(run_model(1:100,
                               nsim = 100,
                               beta = 0.2,
                               sigma = 0.1,
                               I_ini = 10,
                               S_ini = 1000))
})

test_that("population remains constant", {
  nsim <- 10
  I_ini <- 10
  S_ini <- 1000
  res <- run_model(1:100,
                 nsim = nsim,
                 beta = 0.2,
                 sigma = 0.1,
                 I_ini = I_ini,
                 S_ini = S_ini)

  N <- S_ini + I_ini

  res <- res[, -1]
  sims <- lapply(1:nsim, function(x) res[, seq_len(ncol(res)) %% nsim == nsim - x])
  pops <- sapply(sims, function(s) all(apply(s, 1, sum) == N))
  expect_true(all(pops))
})
