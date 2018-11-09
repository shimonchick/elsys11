class CatsController < ApplicationController
  def new
  
  end

  def create
  end

  def index
    @cats = Cat.all
  end

  def show
    #render plain: params[:id]
    @cat = Cat.find(params[:id])
  end
end
