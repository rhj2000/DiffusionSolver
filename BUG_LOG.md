# 20260228-4

### Bug: Solver is not computing solution correctly

Cause: FTCS implementation is incorect
	
```math
\text{former: } u_{n+1}=s+dt\cdot u_n+dt \cdot \alpha \Delta u_n
```

Solution: Write the implementation correctly dummy.

```math
\text{new: } u_{n+1} = u_n + s\cdot dt + \alpha \cdot dt \cdot \Delta u_n
```


# 20260228-3

### Bug: At large grid sizes, solutions blow up.

# 20260228-2

### Bug: When dt is set to 1, solver sets the grid as all ones.

# 20260228-1

### Bug: Solver does not compute properly for NxN wherein N is even.

Symptoms:
```
1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 1
1 0.00724945 0.0024126 0.0024126 0.0024126 0.0024126 0.00724945 1
1 0 0 0 0 0 0 1
1 0.0048485 5.82064e-06 5.82064e-06 5.82064e-06 5.82064e-06 0.0048485 1
1 0 0 0 0 0 0 1
1 0.00241845 1.4009e-08 1.4009e-08 1.4009e-08 1.4009e-08 0.00241845 1
1 1 1 1 1 1 1 1
```

Even rows (odd indexed) are not evolving with time.

Cause: update of solution was declared in wrong scope
```
for (int i{ 1 }; i < nx - 1; i++) {
			for (int j{ 1 }; j < ny - 1; j++) {
			u_new_[k] = ...
			}
			u_.swap(u_new_);
	}
```

Fix: Move update code to proper scope--after the entire matrix is calculated for the timestep

```
for (int t{ 0 }; t < steps; t++) {
	for (int i{ 1 }; i < nx - 1; i++) {
				for (int j{ 1 }; j < ny - 1; j++) {
				u_new_[k] = ...
				}
		}
	u_.swap(u_new_);
}
```
