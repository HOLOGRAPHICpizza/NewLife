PROGRAM SteerClear IS #comment
    INSTRUCTION StepAside IS
        IF random THEN
            turnright
        ELSE
            turnleft
        END IF
        move
    END StepAside
    
    INSTRUCTION TurnAround IS
        turnright
        turnright
    END TurnAround
    
BEGIN
    WHILE true DO
        IF next-is-empty THEN
            skip
        ELSE
            IF next-is-wall THEN
                TurnAround
            ELSE
                StepAside
            END IF
        END IF
    END WHILE
END SteerClear
