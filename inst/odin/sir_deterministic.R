## Core equations for transitions between compartments:
update(S) <- S - beta * S * I / N
update(I) <- I + beta * S * I / N - sigma * I
update(R) <- R + sigma * I

## Total population size (odin will recompute this at each timestep:
## automatically)
N <- S + I + R

## Initial states:
initial(S) <- S_ini # will be user-defined
initial(I) <- I_ini # will be user-defined
initial(R) <- 0

## User defined parameters - default in parentheses:
S_ini <- user()
I_ini <- user()
beta <- user()
sigma <- user()