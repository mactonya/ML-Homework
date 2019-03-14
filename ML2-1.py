import ipywidgets as wgt
import math
import random

def is_prime(x):
    for i in range(2,math.ceil(math.sqrt(x))+1):
        if (x % i) == 0:
                return False
    return True

def get_prime(digits):
    while True:
        p = random.getrandbits(digits)
        if is_prime(p) and p > 2:
            return p

def ext_euclid(a, b):
     if b == 0:
         return 1, 0, a
     else:
         x, y, q = ext_euclid(b, a % b) # q = gcd(a, b) = gcd(b, a%b)
         x, y = y, (x - (a // b) * y)
         return x, y, q


def prepare_RSA(digits):
    
    # Take 2 primes
    p = get_prime(digits)
    q = get_prime(digits)
    N = p*q
    tolient_product = (p-1)*(q-1)

    # Find a random int that is coprime w/ tolient_product
    while True:
        e = random.randint(2,tolient_product)
        if ext_euclid(e, tolient_product)[2] == 1:
            break

    # Find its modular multiplicative inverse using Extended Euclidean algorithm
    l = ext_euclid(e, tolient_product)[0] 
    if l < 0:
        l += tolient_product
    return N, e, l


[N,e,l] = prepare_RSA(8)



def example(strs):
    print("This example uses 8 bit RSA")
    print("You entered " + strs)
    

    origin = []
    for chrs in strs:
        origin.append((ord(chrs)))
    print("The corresponding ASCII code(s) is", origin)

    print("The public key is (",N,", ",e,")")

    encode = []

    for num in origin:
        encode.append((num**e)%N)
    print("The encoded message is", encode)

    print("The private key is (",N,", ",l,")")

    decode = []

    for num in encode:
        decode.append((num**l)%N)

    print("The decoded message is", decode, ", that is,")

    
    result = []
    for ch in decode:
        result.append(chr(int(ch)))
        
    print(result, ". Hooray!")
        
wgt.interact(example, strs = '')