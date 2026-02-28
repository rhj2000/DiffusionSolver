# 20260228 - 1

### Checkerboard pattern.

Given certain parameters, a checkerboard pattern forms. 

See this with the following parameters:
```
nx = 40
ny = 40
lx = 5
ly = 5
dt = 0.01
alpha = 0.25

source function s:
if (i < nx / 2 + 2 && i > nx / 2 - 2) {
	if (j < ny / 2 + 2 && j > ny / 2 - 2) {
		s = 3;
	}
}

1000 timesteps
```

Cause: Not quite known. Some instability?

Solution: Don't use too fine of a timestep or too fine of a grid.

Notes: Can't replicate this after fixing FTCS implementation problem.