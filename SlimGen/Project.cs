using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;
using System.Reflection;

namespace SlimGen
{
    namespace Generator
    {
        class ReplaceMethodNativeAttribute : Attribute
        {
        }
    }

    class Project
    {
        public string FileName
        {
            get;
            private set;
        }

        public bool Changed
        {
            get;
            set;
        }

        public Build Build
        {
            get;
            private set;
        }

        public Project(Build build)
        {
            Build = build;
        }

        public Project(string assemblyName)
        {
            Build = new Build();
            Build.Assembly = assemblyName;
            Build.Platforms = new Platform[2];
            Build.Platforms[0] = new Platform() { Type = PlatformSpecifier.X86 };
            Build.Platforms[1] = new Platform() { Type = PlatformSpecifier.X64 };

            List<Method> methods = new List<Method>();
            var file = new FileInfo(assemblyName);
            var assembly = file.Exists ? Assembly.ReflectionOnlyLoadFrom(file.FullName) : Assembly.ReflectionOnlyLoad(assemblyName);

            foreach (var type in assembly.GetTypes())
            {
                foreach (var method in type.GetMethods(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static))
                {
                    foreach (var attribute in CustomAttributeData.GetCustomAttributes(method))
                    {
                        if (attribute.ToString().Trim('{', '[', '(', ')', ']', '}') == typeof(SlimGen.Generator.ReplaceMethodNativeAttribute).FullName)
                        {
                            methods.Add(new Method() { Name = type.FullName + "." + method.Name });
                            break;
                        }
                    }
                }
            }

            Build.Platforms[0].Methods = methods.ToArray();
            Build.Platforms[1].Methods = methods.ToArray();

            Changed = true;
        }

        public static Project FromFile(string fileName)
        {
            Build build = null;

            var serializer = new XmlSerializer(typeof(Build));
            try
            {
                using (var file = new FileStream(fileName, FileMode.Open))
                    build = (Build)serializer.Deserialize(file);
            }
            catch (Exception)
            {
                MessageBox.Show("Invalid project file.", "SlimGen", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }

            Project project = new Project(build);
            project.FileName = fileName;

            return project;
        }

        public void Save(string fileName)
        {
            if (!Changed && !string.IsNullOrEmpty(FileName) && fileName == FileName)
                return;

            var serializer = new XmlSerializer(typeof(Build));
            try
            {
                using (var file = new FileStream(fileName, FileMode.Open))
                    serializer.Serialize(file, Build);
            }
            catch (Exception)
            {
                MessageBox.Show("Error occurred while saving project.", "SlimGen", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Changed = false;
        }
    }
}
