using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace SlimGen
{
    static class Signature
    {
        public static string Build(MethodInfo method)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append("(");

            var parameters = method.GetParameters();
            foreach (var parameter in parameters)
            {
                if (parameter.IsOut)
                    builder.Append(parameter.IsIn ? "ref " : "out ");

                builder.Append(parameter.ParameterType.FullName);
                builder.Append(", ");
            }

            if (parameters.Length != 0)
                builder.Length -= 2;

            builder.Append(")");
            return builder.ToString();
        }
    }
}
