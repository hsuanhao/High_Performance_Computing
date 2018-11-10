#metropolis_Problem4.py
import math
import random

class Metropolis :
    def __init__(self, delta=1.0) : 
        self.x = 0.0             # initial position of walker
        self.delta = delta       # step size
        self.accepts = 0         # number of steps accepted

    def step(self):
        x_trial = self.x + self.delta * random.uniform(-1, 1)
        ratio = self.P(x_trial) / self.P(self.x)
        if (ratio > random.random()):
            self.x = x_trial
            self.accepts += 1
                
    def P(self, x):
        # normalized Gaussian function
        return math.exp(-x**2 / 2.0) / math.sqrt(2 * math.pi)

    def f_over_w(self):
        # integrand divided by weight function
        return float(self.x**2)


print " Monte Carlo Quadrature using Metropolis et al. Algorithm"
print " ========================================================"
delta = float(input(" Enter step size delta: "))
M = int(input(" Enter number of trials M: "))
#number of Metropolis steps per trial N
# = number of trials M

Nsteps = [M,M,M,M,M]
std = []

for k in range(5):
    f_sum = 0.0         # accumulator for f(x) values
    f2_sum = 0.0        # [f(x)]**2 values
    err_sum = 0.0       # error estimates
    Acc = 0.0
    metropolis = Metropolis( delta=delta )
    for i in range(Nsteps[k]):
        avg = 0.0
        var = 0.0
        for j in range(Nsteps[k]):
            metropolis.step()
            fx = metropolis.f_over_w()
            avg += fx
            var += fx**2
        avg /= float(Nsteps[k])
        var /= float(Nsteps[k])
        var = var - avg**2
        err = math.sqrt(var / Nsteps[k])
        f_sum += avg
        f2_sum += avg**2
        err_sum += err
    ans = f_sum / float(Nsteps[k])
    acc = abs(ans - 1.0)/ 1.0
    std_dev = math.sqrt(f2_sum / Nsteps[k] - ans * ans)
    std_dev /= math.sqrt(Nsteps[k]-1.0)
    err = err_sum / float(Nsteps[k])
    err /= math.sqrt(Nsteps[k])
    std.append(std_dev)
    print ""
    print " Exact answer =", 1.0
    print "     Integral =", ans, "+-", err
    print "    Std. Dev. =", std_dev
    print " Accept ratio =", metropolis.accepts / float(Nsteps[k]*Nsteps[k])
    print "          Acc =", acc

print " std =", std #Check answer

avg_std = 0.0
for l in range(5):
  avg_std += std[l]
avg_std /= float(5)
print "average std =", avg_std


    
