import numpy as np
import torch

observation = np.array([0.0, 0.0], dtype=np.float32)
obv_tensor = torch.from_numpy(observation)

print(observation)
print(obv_tensor)
