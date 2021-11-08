test_that("average of stochastic realisations approximates deterministic solution", {
  S_ini <- 1000
  I_ini <- 20 # seed reasonably high to avoid early extinction events
  res <- run_model(1:100,
                   nsim = 10000,
                   beta = 0.3,
                   sigma = 0.1,
                   I_ini = I_ini,
                   S_ini = S_ini)
  det <- run_model_deterministic(1:100,
                                 beta = 0.3,
                                 sigma = 0.1,
                                 I_ini = I_ini,
                                 S_ini = S_ini)

  res <- as.data.frame(res)

  S <- res %>%
    dplyr::select(contains("S["))

  I <- res %>%
    dplyr::select(contains("I["))

  R <- res %>%
    dplyr::select(contains("R["))

  # this tolerance is totally arbitrary, I don't understand the dynamics of
  # the system well enough to understand what sort of difference to expect here
  expect_true(all(abs(rowMeans(S) - det[, "S"]) < 30))
  expect_true(all(abs(rowMeans(I) - det[, "I"]) < 30))
  expect_true(all(abs(rowMeans(R) - det[, "R"]) < 30))
})

# unfortunately we can't do a similar test for arbitrary time steps because the probabilities
# at each time depend on the states of the compartments so deviate between realisations
test_that("infection follows expected binomial distribution in first step", {
  nsim <- 100
  beta <- 0.2
  sigma <- 0
  S_ini <- 10000
  I_ini <- 1
  res <- run_model(1:100, nsim = nsim, beta = beta, sigma = sigma, I_ini = I_ini, S_ini = S_ini)

  infected_t1 <- res %>%
    as.data.frame() %>%
    dplyr::slice(1) %>%
    dplyr::select(contains("I["))

  infected_t2 <- res %>%
    as.data.frame() %>%
    dplyr::slice(2) %>%
    dplyr::select(contains("I["))

  new_infections_t2 <- infected_t2 - infected_t1

  p <- 1 - exp(-beta * I_ini / (S_ini + I_ini))
  expected_val <- S_ini * p
  t <- t.test(as.numeric(as.vector(new_infections_t2)), mu = expected_val)
  expect_gt(t$p.value, 0.01) # of course we have to somehow take into account that this will fail 1% of the time
})

test_that("recovery follows expected binomial distribution in first step", {
  nsim <- 100
  beta <- 0
  sigma <- 0.2
  S_ini <- 10000
  I_ini <- 10
  res <- run_model(1:100, nsim = nsim, beta = beta, sigma = sigma, I_ini = I_ini, S_ini = S_ini)

  recovered_t2 <- res %>%
    as.data.frame() %>%
    dplyr::slice(2) %>%
    dplyr::select(contains("R["))

  p <- 1 - exp(-sigma)
  expected_val <- I_ini * p
  t <- t.test(as.numeric(as.vector(recovered_t2)), mu = expected_val)
  expect_gt(t$p.value, 0.05)
})

get_num_full_fadeouts <- function(res, nsim, S_ini) {
  end <- res %>%
    as.data.frame() %>%
    dplyr::slice_tail()

  end_S <- end %>%
    dplyr::select(contains("S["))

  # num realisations where no susceptibles became infected
  sum(sapply(1:nsim, function(i) ifelse(end_S[, i] == S_ini, 1, 0)))
}

# does this really test anything different from the previous tests? feels like there should
# be something to test here around extinction rates but I'm not sure
test_that("some epidemics never take off", {
  nsim <- 10000
  res <- run_model(1:100,
                   nsim = nsim,
                   beta = 0.2,
                   sigma = 0.1,
                   I_ini = 1,
                   S_ini = 1000)
  num_fadeouts <- get_num_full_fadeouts(res, nsim, 1000)
  expect_gt(num_fadeouts, 1)
})
