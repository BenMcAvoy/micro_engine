SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

MARGIN = 40

PERIOD_X = 3.0
PERIOD_Y = 2.3

local elapsed = 0

function script:load()
    print("script:load() called")
end

function script:update(dt)
    elapsed = elapsed + dt

    local tx = (math.sin(elapsed * (2 * math.pi / PERIOD_X)) + 1) * 0.5
    local ty = (math.sin(elapsed * (2 * math.pi / PERIOD_Y)) + 1) * 0.5

    self.transform.position.x = MARGIN + tx * (SCREEN_WIDTH - 2 * MARGIN)
    self.transform.position.y = MARGIN + ty * (SCREEN_HEIGHT - 2 * MARGIN)
end

function script:draw()
    print("script:draw() called")
end