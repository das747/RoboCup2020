import pygame
import math

pygame.init()
width, height = 1002, 700
screen = pygame.display.set_mode((width, height))
clock = pygame.time.Clock()
fps = 30

k = 2
x, y = width // 4, height - 1
var = {'l': 100, 'h1': 75, 'h2': 75, 'b': 40}


def get(char):
    return var[char] * k


mod = None
font = pygame.font.Font(None, 30)
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            pressed = pygame.key.get_pressed()
            # print(pressed)
            if mod in var and pressed[pygame.K_UP]:
                var[mod] += 1
            elif mod in var and pressed[pygame.K_DOWN]:
                var[mod] -= 1
            elif pressed[pygame.K_ESCAPE]:
                var = {'l': 100, 'h1': 75, 'h2': 75, 'b': 40}
            else:
                mod = ''.join(map(lambda i: chr(i) * pressed[i], range(len(pressed))))[::-1]
            # print(mod)
    var['g'] = math.atan(var['l'] / (var['h1'] + var['h2']))
    var['a'] = (math.pi - var['g']) / 2
    var['r'] = var['h1'] / (1 / math.tan(math.radians(40)) - 1 / math.tan(var['a']))
    ray = get('h1') / math.sin(var['a'] - math.radians(var['b'])) * math.sin(math.pi - var['a'])
    dist = (math.sin(math.radians(var['b'])) * ray +
            (get('h2') + math.cos(math.radians(var['b'])) * ray) *
            math.tan(math.pi - var['a'] * 2 + math.radians(var['b'])))
    var['d'] = dist / k
    screen.fill((0, 0, 0))
    pygame.draw.polygon(screen, (0, 0, 125), ((x - get('l'), y),
                                              (x + get('l'), y),
                                              (x + get('l') - math.tan(var['g']) * get('h2'),
                                               y - get('h2')),
                                              (x - get('l') + math.tan(var['g']) * get('h2'),
                                               y - get('h2'))))
    pygame.draw.polygon(screen, (0, 125, 0), ((x, y - get('h1') - get('h2')),
                                              (x + get('r'),
                                               y - get('h1') - get('h2') - 1 / math.tan(
                                                       var['a']) * get('r')),
                                              (x - get('r'),
                                               y - get('h1') - get('h2') - 1 / math.tan(
                                                       var['a']) * get('r'))))
    ray = get('h1') / math.sin(var['a'] - math.radians(var['b'])) * math.sin(math.pi - var['a'])
    dist = (math.sin(math.radians(var['b'])) * ray +
            (get('h2') + math.cos(math.radians(var['b'])) * ray) *
            math.tan(math.pi - var['a'] * 2 + math.radians(var['b'])))
    pygame.draw.lines(screen, (255, 255, 0), 0, ((x, y - get('h2')),
                                                 (x + math.sin(math.radians(var['b'])) * ray,
                                                  y - get('h2') - math.cos(
                                                      math.radians(var['b'])) * ray),
                                                 (x + dist, y)))
    pygame.draw.circle(screen, (125, 0, 0), (x, y - get('h2')), 5)
    for i, param in enumerate(var):
        text = font.render(
            param + ': ' + str(math.degrees(var[param]) if param in 'ag' else var[param]),
            1, (0, 255 * (mod == param), 255))
        screen.blit(text, (int(x * 2.5), 30 * (i + 1)))
    pygame.display.flip()
    clock.tick(fps)

pygame.quit()
