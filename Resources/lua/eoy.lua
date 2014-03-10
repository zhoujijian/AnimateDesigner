local BONES_ROOTER_TAGID = 6000
local KEYFRAME_COLLECTID = 1

local tracker = { }
local trackid = 0
local logger = function(...) print(string.format(...)) end

local function iter(root, f)
	local cr = root:getChildren()
	if cr then
		for i = 0, cr:count() - 1 do
			local c = tolua.cast(cr:objectAtIndex(i), "CCNode")
			local r = iter(c, f)
			if r then return r end
		end
	end

	return f(root)
end

local function regtrack(ref, slot)
	assert(not tracker[ref], "reg repeat")
	
	slot = slot or { }
	slot.id = trackid	
	trackid = trackid + 1
	tracker[ref] = slot

	return tracker[ref]
end

local function gettrack(ref)
	assert(ref)
	return tracker[ref]
end

local function gettrack_byid(id)
	for _, v in pairs(tracker) do
		if v.id == id then
			return v
		end
	end
end

local function getrect(name)
	local sfr = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName(name)
	assert(sfr, name)
	local rect = sfr:getRect()
	return rect
end

local function getsrc(ko)
	local name = ko:getkey_frame()
	assert(name, "no frame")

	local rect = getrect(name)	
	local blx, bly = rect.origin.x, rect.origin.y
	local tlx, tly = blx, rect.origin.y + rect.size.height
	local trx, try = rect.origin.x + rect.size.width, tly
	local brx, bry = trx, bly
	
	return { blx, bly, tlx, tly, trx, try, brx, bry }
end

local function EC(n)
	return n
end

local function getscreen(ko)
	local name = ko:getkey_frame()
	assert(name, "no frame")

	local rect = getrect(name)
	local blx, bly = ko:get_posx(), ko:get_posy()
	local tlx, tly = blx, bly + rect.size.height
	local trx, try = blx + rect.size.width, tly
	local brx, bry = trx, bly
	
	return { EC(blx), EC(bly), EC(tlx), EC(tly), EC(trx), EC(try), EC(brx), EC(bry) }
end

local function gettexid(ko)
	local name = ko:gettex_name()
	assert(name, "no tex file")

	local _, _, texid = string.find(name, "%a+(%d+).%a+")
	assert(texid, string.format("tex file %s, format error", name))
	return tonumber(texid)
end

local function genpic(ko)
	local key = { }
	key.src = getsrc(ko)
	key.tex = gettexid(ko)
	key.screen = getscreen(ko)
					
	local pi = regtrack(ko)
	pi.type = "picture"
	pi[KEYFRAME_COLLECTID] = key

	logger("generate picture id %d, tex %d", pi.id, pi[KEYFRAME_COLLECTID].tex)

	return pi
end

local function genbone(anio, cur)
	local cr = node:getChildren()
	if cr then
		for i = 0, cr:count() - 1 do
			local c = tolua.cast(cr:objectAtIndex(i), "CCNode")
			local a = tolua.cast(c:getUserObject(), "AnimateObject")
			if a then
				local t = gettrack(c)
				table.insert(cur.component, { id = t.id })
			end
		end

		cur[KEYFRAME_COLLECTID][1] = { }
		for i = 1, #cur.component do
			table.insert(cur[KEYFRAME_COLLECTID][1], i - 1)
		end
	end
end

local function genanim(anio, cur, eoy)
	local lki
	local seq = anio:getseq()
	logger("animate key frame count %d", seq:count())

	for i = 0, seq:count() - 1 do
		local ko = tolua.cast(seq:objectAtIndex(i), "KeyFrameObject")
		local pi = genpic(ko)
		table.insert(eoy, pi)
		table.insert(cur.component, { id = pi.id })

		lki = lki or ko:getkey_index()
		if i > 0 then
			for k = lki, ko:getkey_index() - 1 do
				table.insert(cur[KEYFRAME_COLLECTID], { i - 1 })
			end
			lki = ko:getkey_index()
		end
	end
	if seq:count() > 0 then
		table.insert(cur[KEYFRAME_COLLECTID], { seq:count() - 1 })
	end
end

local function geneoy()
	local scene = CCDirector:sharedDirector():getRunningScene()
	local boner = iter(scene, function(node)
		if node:getTag() == BONES_ROOTER_TAGID then
			return node
		end
	end)
	assert(boner, "bone root not found")
	logger("boner root found [%d]", boner:getTag())

	local eoy = { }
	iter(boner, function(node)
		if boner == node then return end
		local anio = tolua.cast(node:getUserObject(), "AnimateObject")
		if not anio then return end

		local comp = { type = "animation", component = { } }
		comp[KEYFRAME_COLLECTID] = { }

		if anio:isbone() then
			logger("# <start> generate bone node component #")
			genbone(anio, comp)
			logger("# <end> #")
		else
			logger("# <start> generate anim node component #")
			genanim(anio, comp, eoy)
			logger("# <end> #")
		end

		regtrack(node, comp)
		logger("register tracker animation [%d]", comp.id)

		table.insert(eoy, comp)
	end)

	return eoy
end

local function clear()
	trackid = 0
	tracker = { }
end


local ejoy = { geneoy = geneoy, clear = clear }
return ejoy