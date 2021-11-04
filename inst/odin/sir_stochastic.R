## Core equations for transitions between compartments:
update(S[]) <- S[i] - n_SI[i]
update(I[]) <- I[i] + n_SI[i] - n_IR[i]
update(R[]) <- R[i] + n_IR[i]

## Individual probabilities of transition:
p_SI[] <- 1 - exp(-beta * I[i] / N[i])
p_IR <- 1 - exp(-sigma)

## Draws from binomial distributions for numbers changing between
## compartments:
n_SI[] <- rbinom(S[i], p_SI[i])
n_IR[] <- rbinom(I[i], p_IR)

## Total population size
N[] <- S[i] + I[i] + R[i]

## Initial states:
initial(S[]) <- S_ini
initial(I[]) <- I_ini
initial(R[]) <- 0

## User defined parameters - default in parentheses:
S_ini <- user()
I_ini <- user()
beta <- user()
sigma <- user()

## Number of replicates
nsim <- user()
dim(N) <- nsim
dim(S) <- nsim
dim(I) <- nsim
dim(R) <- nsim
dim(p_SI) <- nsim
dim(n_SI) <- nsim
dim(n_IR) <- nsim
