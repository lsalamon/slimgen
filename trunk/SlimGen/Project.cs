using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using System.Windows.Forms;
using System.Reflection;

namespace SlimGen
{
    [Serializable]
    [XmlType("slimgen.build")]
    public class Project
    {
        [XmlElement("platform")]
        public Platform[] Platforms = new Platform[2];

        [XmlAttribute("assembly")]
        public string AssemblyName;

        [XmlIgnore]
        public string FileName
        {
            get;
            private set;
        }

        [XmlIgnore]
        public bool Changed
        {
            get;
            set;
        }

        [XmlIgnore]
        public Platform PlatformX86
        {
            get { return Platforms[0]; }
            private set { Platforms[0] = value; }
        }

        [XmlIgnore]
        public Platform PlatformX64
        {
            get { return Platforms[1]; }
            private set { Platforms[1] = value; }
        }

        private Project()
        {
            PlatformX86 = new Platform(PlatformSpecifier.X86);
            PlatformX64 = new Platform(PlatformSpecifier.X64);
        }

        public Project(string assemblyName)
            : this()
        {
            AssemblyName = assemblyName;

            var methods = ExtractMethods(assemblyName);
            PlatformX86.Methods = methods;
            PlatformX64.Methods = new List<Method>(methods);

            Changed = true;
        }

        public static Project FromFile(string fileName)
        {
            Project project = null;

            var serializer = new XmlSerializer(typeof(Project));
            try
            {
                using (var file = new FileStream(fileName, FileMode.Open))
                    project = (Project)serializer.Deserialize(file);
            }
            catch (Exception)
            {
                MessageBox.Show("Invalid project file.", "SlimGen", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }

            project.FileName = fileName;
            return project;
        }

        public void Save(string fileName)
        {
            if (!Changed || (!string.IsNullOrEmpty(FileName) && fileName == FileName))
                return;

            var serializer = new XmlSerializer(typeof(Project));
            try
            {
                using (var file = new FileStream(fileName, FileMode.Create))
                    serializer.Serialize(file, this);
            }
            catch (Exception)
            {
                MessageBox.Show("Error occurred while saving project.", "SlimGen", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Changed = false;
        }

        public void Refresh()
        {
        }

        static List<Method> ExtractMethods(string assemblyName)
        {
            var methods = new List<Method>();
            var file = new FileInfo(assemblyName);
            var assembly = file.Exists ? Assembly.ReflectionOnlyLoadFrom(file.FullName) : Assembly.ReflectionOnlyLoad(assemblyName);

            foreach (var type in assembly.GetTypes())
            {
                foreach (var method in type.GetMethods(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static))
                {
                    foreach (var attribute in CustomAttributeData.GetCustomAttributes(method))
                    {
                        if (attribute.ToString() == "[SlimGen.Generator.ReplaceMethodNativeAttribute()]")
                        {
                            methods.Add(new Method(type.FullName + "." + method.Name, Signature.Build(method)));
                            break;
                        }
                    }
                }
            }

            return methods;
        }
    }
}
