__author__ = 'edenlin'
import web

render = web.template.render('templates/')

urls = (
    '/(.*)', 'index'
)

app = web.application(urls, globals())

class index:
    def GET(self, name):
        #i = web.input(name=None)
        #name = 'Eden'
        return render.index(name)

if __name__ == "__main__":app.run()