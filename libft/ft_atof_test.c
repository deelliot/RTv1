/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:25:20 by thakala           #+#    #+#             */
/*   Updated: 2022/11/09 19:16:55 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int	ft_test(const char *numeric_literal, double numeric_value, uint64_t line)
{
	double	result_value;

	result_value = ft_atof(numeric_literal);
	printf("ft_atof_test.c:%llu:\n", line);
	printf("\t____input: %42s\n", numeric_literal);
	printf("\t_expected: % 42lf\n", numeric_value);
	printf("\t___result: % 42lf\n", result_value);
	return (result_value == numeric_value);
}

int	ft_precision_loop(double numeric_value, uint64_t line)
{
	char		*original_numeric_literal;
	uint8_t		precision;
	double		original_numeric_value;

	precision = 0;
	while (precision < 42)
	{
		asprintf(&original_numeric_literal, "%.*lf", precision, numeric_value);
		original_numeric_value = atof(original_numeric_literal);
		ft_test(original_numeric_literal, original_numeric_value, line);
		free(original_numeric_literal);
	}
}

int	ft_random_floating_point_value(uint64_t line)
{
	uint64_t	integral;
	uint64_t	fractional;
	double		fractional_double;
	double		horribly_not_random_double;

	arc4random_buf(&integral, sizeof(integral));
	arc4random_buf(&fractional, sizeof(integral));
	fractional_double = (double)fractional / (double)(uint64_t)(-1);
	while (1 > fractional_double)
		fractional_double *= 10;
	fractional_double /= 10;
	horribly_not_random_double = (double)integral + fractional_double;
	ft_precision_loop();
}

int	ft_random_floating_point_value_from_uint64_t(uint64_t line)
{
	uint64_t	integral;


}

int	main(void)
{
	if (!ft_test("", (double)0, __LINE__)
		|| !ft_test("-33", -(double)33, __LINE__)
		|| !ft_test("-10", -(double)10, __LINE__)
		|| !ft_test("-9", -(double)9, __LINE__)
		|| !ft_test("-8", -(double)8, __LINE__)
		|| !ft_test("-7", -(double)7, __LINE__)
		|| !ft_test("-6", -(double)6, __LINE__)
		|| !ft_test("-5", -(double)5, __LINE__)
		|| !ft_test("-4", -(double)4, __LINE__)
		|| !ft_test("-3", -(double)3, __LINE__)
		|| !ft_test("-2", -(double)2, __LINE__)
		|| !ft_test("-1", -(double)1, __LINE__)
		|| !ft_test("0", -(double)0, __LINE__)
		|| !ft_test("1", (double)1, __LINE__)
		|| !ft_test("2", (double)2, __LINE__)
		|| !ft_test("3", (double)3, __LINE__)
		|| !ft_test("4", (double)4, __LINE__)
		|| !ft_test("5", (double)5, __LINE__)
		|| !ft_test("6", (double)6, __LINE__)
		|| !ft_test("7", (double)7, __LINE__)
		|| !ft_test("8", (double)8, __LINE__)
		|| !ft_test("9", (double)9, __LINE__)
		|| !ft_test("10", (double)10, __LINE__)
		|| !ft_test("33", (double)33, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__)
		|| !ft_test("", (double)0, __LINE__))
	{
		printf("KO: ft_atof\n");
		return (EXIT_FAILURE);
	}
	printf("OK: ft_atof\n");
	return (EXIT_SUCCESS);
}
