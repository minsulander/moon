function moon.Component:onInitialize()
	temp = self:getTemplate()
	if (temp) then
		if (temp.onInitialize ~= self.onInitialize) then
			temp.onInitialize(self)
		end
		-- Copy template callbacks
		if (not self.onReset) then self.onReset = temp.onReset; end
		if (not self.onRealize) then self.onRealize = temp.onRealize; end
		if (not self.onUnrealize) then self.onUnrealize = temp.onUnrealize; end
		if (not self.onContact) then self.onContact = temp.onContact; end
		if (not self.onContactFeedback) then self.onContactFeedback = temp.onContactFeedback; end
		if (not self.onUpdate) then self.onUpdate = temp.onUpdate; end
	end
end
