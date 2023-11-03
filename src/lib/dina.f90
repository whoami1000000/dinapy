subroutine add(a, b, res) bind (c, name = "add")
    use iso_c_binding
    implicit none

    integer(c_int), value, intent(in) :: a, b
    integer(c_int), intent(out) :: res

    res = a + b
end subroutine add

subroutine sum_numbers(numbers, len, res) bind (c, name = "sum_numbers")
    use iso_c_binding
    implicit none

    integer(c_size_t), value, intent(in) :: len
    integer(c_int), dimension(len), intent(in) :: numbers
    integer(c_int), intent(out) :: res

    res = sum(numbers)
end subroutine sum_numbers