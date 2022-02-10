try:
    import configparser
except ImportError:
    import ConfigParser as configparser

Import("env")

config = configparser.ConfigParser()
config.read("platformio.ini")

try:
    script = config.get(f"env:{env['PIOENV']}", "ruby_path")
except configparser.NoOptionError:
    script = config.get(f"env", "ruby_path")

env.Execute(f"mrbc -B bin -o include/mrb.h {script}")
