[top]
components : constantFreqGen@ConstantFreqGen 
out : outt
in : start stop
link : start start@constantFreqGen
link : stop stop@constantFreqGen
link : out@constantFreqGen outt