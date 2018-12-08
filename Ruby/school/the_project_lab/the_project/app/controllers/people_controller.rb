class PeopleController < ApplicationController

def create
    person = Person.create(params.require(:person).permit(:first_name, :last_name, :age, :sex))
    redirect_to person_path(person)
end

def show
    @person = Person.find(params[:id])
end
def index

end

def update

end

def new
    @person = Person.new
end

def read

end

def delete

end


end
