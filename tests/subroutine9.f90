subroutine a()
import, none
implicit none
end subroutine

subroutine b()
import, all
implicit none
end subroutine

subroutine c()
import a, b
implicit none
end subroutine

subroutine d()
import :: a, b
implicit none
end subroutine

subroutine e()
import, only: a, b
implicit none
end subroutine
