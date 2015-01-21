/* Copyright (C) 2001-2014 Free Software Foundation, Inc.

   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <fenv.h>
#include <fpu_control.h>

int
fedisableexcept (int excepts)
{
  fpu_control_t fpcr;
  fpu_control_t fpcr_new;
  int original_excepts;

  _FPU_GETCW (fpcr);

  original_excepts = (fpcr >> FE_EXCEPT_SHIFT) & FE_ALL_EXCEPT;

  excepts &= FE_ALL_EXCEPT;

  fpcr_new = fpcr & ~(excepts << FE_EXCEPT_SHIFT);

  if (fpcr != fpcr_new)
    _FPU_SETCW (fpcr_new);

  return original_excepts;
}
